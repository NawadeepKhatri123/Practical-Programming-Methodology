#ifndef MEMORY_ALLOCATION_H
#define MEMORY_ALLOCATION_H

#include <vector>
#include <utility>
#include <random>
#include <algorithm>

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

    void merge_free_blocks();
    bool allocate_memory(int size, long int current_clock);
    void check_and_release_expired_blocks(long int current_clock);
    int generate_block_size();
    int generate_lease_duration();

public:
    MemoryAllocator();
    void run_simulation();
    void print_simulation_results();
};

#endif // MEMORY_ALLOCATION_H
