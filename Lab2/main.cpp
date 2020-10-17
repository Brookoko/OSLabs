#include <iostream>
#include "PageAllocator.h"

int main() {
    try
    {
        auto allocator = PageAllocator(32 * 1024);
        allocator.mem_dump();
        auto loc1 = allocator.mem_alloc(32);
        auto loc2 = allocator.mem_alloc(32);
        auto loc3 = allocator.mem_alloc(32);
        allocator.mem_dump();
        allocator.mem_free(loc1);
        allocator.mem_free(loc2);
        allocator.mem_free(loc3);
        allocator.mem_dump();
    }
    catch (std::exception ex)
    {
        std::cerr << "error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}