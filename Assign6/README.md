Overview
This program simulates memory allocation by handling requests for memory blocks, allocating them using a first-fit allocation strategy, and releasing them when their lease expires. The system manages two lists: a free list (available memory blocks) and an allocated list (currently allocated memory blocks with expiry times). Adjacent free blocks are merged when necessary.

Constants

MIN_LEASE = 40, MAX_LEASE = 70: Lease duration range.

MIN_SIZE = 50, MAX_SIZE = 350: Block size range.

TIME_LIMIT = 1000: Total simulation time.

REQUEST_INTERVAL = 10: Interval for generating memory requests.

MEMORY_SIZE = 1000: Total available memory.

Features

First-Fit Allocation: Allocates the first available block that fits the request.

Lease Expiry: Allocated blocks are returned to the free list after their lease expires.

Block Merging: Adjacent free blocks are merged when a memory request fails.

Statistics: Tracks block sizes, lease durations, and merging operations.
Compilation

To compile the program:

  g++ -o memory_allocator main.cpp memory_allocator.cpp

Running the Program
Run the program:

./memory_allocator

Output

At the end of the simulation, the program will output:

Total requests made
Satisfied and unsatisfied requests
Block size and lease statistics
Number of merges performed
Final free and allocated lists
