#include "memory_allocation.h"
#include <climits>
int main() {
    MemoryAllocator allocator;
    allocator.run_simulation();
    allocator.print_simulation_results();
    return 0;
}
