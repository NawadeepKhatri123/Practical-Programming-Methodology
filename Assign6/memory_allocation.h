#ifndef MEMORY_ALLOCATION_H
#define MEMORY_ALLOCATION_H

#include <vector>
#include <utility>
#include <random>
#include <algorithm>
#include <climits>

// Simulation parameters
const int MIN_LEASE = 40;
const int MAX_LEASE = 70;
const int MIN_SIZE = 50;
const int MAX_SIZE = 350;
const int TIME_LIMIT = 1000;
const int REQUEST_INTERVAL = 10;
const int MEMORY_SIZE = 1000;

// Type definitions
using range = std::pair<int, int>;
using alloc = std::pair<range, int>;

class MemoryAllocator {
private:
    std::vector<range> free_list;
    std::vector<alloc> allocated_list;
    std::mt19937 rng;

    // Statistics tracking
    int total_requests = 0;
    int satisfied_requests = 0;
    int unsatisfied_requests = 0;
    int merge_count = 0;

    // Tracking block size statistics
    int smallest_block = INT_MAX;
    int largest_block = 0;
    long long total_block_size = 0;

    // Tracking lease duration statistics
    int shortest_lease = INT_MAX;
    int longest_lease = 0;
    long long total_lease_duration = 0;

    void merge_free_blocks();
    bool allocate_memory(int size, long int current_clock);
    void check_and_release_expired_blocks(long int current_clock);
    int generate_block_size();
    int generate_lease_duration();
    void update_block_size_stats(int size);
    void update_lease_duration_stats(int lease);

public:
    MemoryAllocator();
    void run_simulation();
    void print_simulation_results();
};

#endif // MEMORY_ALLOCATION_H
