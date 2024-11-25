#include "memory_allocation.h"
#include <iostream>
#include <iomanip>
#include <limits>
#include <climits>
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

void MemoryAllocator::update_block_size_stats(int size) {
    smallest_block = std::min(smallest_block, size);
    largest_block = std::max(largest_block, size);
    total_block_size += size;
}

void MemoryAllocator::update_lease_duration_stats(int lease) {
    shortest_lease = std::min(shortest_lease, lease);
    longest_lease = std::max(longest_lease, lease);
    total_lease_duration += lease;
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
            
            // Track block size statistics
            update_block_size_stats(size);
            
            // Generate and track lease duration
            int lease_duration = generate_lease_duration();
            update_lease_duration_stats(lease_duration);
            
            // Add to allocated list
            int lease_expiry = current_clock + lease_duration;
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
            merge_count++;
        } else {
            ++it;
        }
    }
}

void MemoryAllocator::run_simulation() {
    long int clock = 0;
    
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
                }
            } else {
                satisfied_requests++;
            }
        }
    }
}

void MemoryAllocator::print_simulation_results() {
    std::cout << "Simulation Results:\n";
    
    // Request Statistics
    std::cout << "\nRequest Statistics:\n";
    std::cout << "Total Requests: " << total_requests << "\n";
    std::cout << "Satisfied Requests: " << satisfied_requests << "\n";
    std::cout << "Unsatisfied Requests: " << unsatisfied_requests << "\n";
    
    // Block Size Statistics
    std::cout << "\nBlock Size Statistics:\n";
    std::cout << "Smallest Block: " << smallest_block << "\n";
    std::cout << "Largest Block: " << largest_block << "\n";
    std::cout << "Average Block Size: " 
              << (total_requests > 0 ? total_block_size / total_requests : 0) << "\n";
    
    // Lease Duration Statistics
    std::cout << "\nLease Duration Statistics:\n";
    std::cout << "Shortest Lease: " << shortest_lease << "\n";
    std::cout << "Longest Lease: " << longest_lease << "\n";
    std::cout << "Average Lease Duration: " 
              << (total_requests > 0 ? total_lease_duration / total_requests : 0) << "\n";
    
    // Merge Operations
    std::cout << "\nMerge Operations: " << merge_count << "\n";
    
    // Final State of Lists
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
