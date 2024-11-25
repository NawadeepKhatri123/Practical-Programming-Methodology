#include "memory_allocation.h"
#include <iostream>
#include <iomanip>

MemoryAllocator::MemoryAllocator() : rng(std::random_device{}()) {
    // Initialize free list with the entire memory
    free_list.push_back({0, MEMORY_SIZE});
}

int MemoryAllocator::generate_block_size() {
    std::uniform_int_distribution<> size_dist(MIN_SIZE, MAX_SIZE);
    return size_dist(rng);
}

int MemoryAllocator::generate_lease_duration() {
    std::uniform_int_distribution<> lease_dist(MIN_LEASE, MAX_LEASE);
    return lease_dist(rng);
}

bool MemoryAllocator::allocate_memory(int size, long int current_clock) {
    // First-fit allocation
    for (auto it = free_list.begin(); it != free_list.end(); ++it) {
        if (it->second >= size) {
            range allocated_range = {it->first, size};
            
            // Update free block
            if (it->second == size) {
                free_list.erase(it);
            } else {
                it->first += size;
                it->second -= size;
            }
            
            // Add to allocated list
            int lease_expiry = current_clock + generate_lease_duration();
            allocated_list.push_back({allocated_range, lease_expiry});
            
            // Keep allocated list sorted by lease expiry
            std::sort(allocated_list.begin(), allocated_list.end(), 
                      [](const alloc& a, const alloc& b) { return a.second < b.second; });
            
            return true;
        }
    }
    return false;
}

void MemoryAllocator::check_and_release_expired_blocks(long int current_clock) {
    auto it = allocated_list.begin();
    while (it != allocated_list.end() && it->second <= current_clock) {
        // Return block to free list
        range block_to_free = it->first;
        free_list.push_back(block_to_free);
        
        // Remove from allocated list
        it = allocated_list.erase(it);
        
        // Keep free list sorted
        std::sort(free_list.begin(), free_list.end(), 
                  [](const range& a, const range& b) { return a.first < b.first; });
    }
}

void MemoryAllocator::merge_free_blocks() {
    if (free_list.size() <= 1) return;
    
    std::sort(free_list.begin(), free_list.end(), 
              [](const range& a, const range& b) { return a.first < b.first; });
    
    for (auto it = free_list.begin(); it != free_list.end() - 1; ) {
        auto next = it + 1;
        if (it->first + it->second == next->first) {
            // Merge adjacent blocks
            it->second += next->second;
            free_list.erase(next);
        } else {
            ++it;
        }
    }
}

void MemoryAllocator::run_simulation() {
    long int clock = 0;
    int total_requests = 0;
    int satisfied_requests = 0;
    int unsatisfied_requests = 0;
    int merge_count = 0;

    while (++clock <= TIME_LIMIT) {
        // Check and release expired blocks
        check_and_release_expired_blocks(clock);
        
        // Generate memory request at intervals
        if (clock % REQUEST_INTERVAL == 0) {
            total_requests++;
            int block_size = generate_block_size();
            
            if (!allocate_memory(block_size, clock)) {
                // Attempt merging if allocation fails
                merge_free_blocks();
                if (!allocate_memory(block_size, clock)) {
                    unsatisfied_requests++;
                } else {
                    satisfied_requests++;
                    merge_count++;
                }
            } else {
                satisfied_requests++;
            }
        }
    }
}

void MemoryAllocator::print_simulation_results() {
    std::cout << "Simulation Results:\n";
    std::cout << "Total Requests: " << satisfied_requests + unsatisfied_requests << "\n";
    std::cout << "Satisfied Requests: " << satisfied_requests << "\n";
    std::cout << "Unsatisfied Requests: " << unsatisfied_requests << "\n";
    
    // Print final state of free and allocated lists
    std::cout << "\nFinal Free List:\n";
    for (const auto& block : free_list) {
        std::cout << "Start: " << block.first 
                  << ", Size: " << block.second << "\n";
    }
    
    std::cout << "\nFinal Allocated List:\n";
    for (const auto& block : allocated_list) {
        std::cout << "Start: " << block.first.first 
                  << ", Size: " << block.first.second 
                  << ", Expires: " << block.second << "\n";
    }
}
