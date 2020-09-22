#include <iostream>
#include "Allocator.h"

void test1()
{
    Allocator allocator = Allocator(1024);
    allocator.mem_dump();
    std::cout << std::endl;

    void *location = allocator.mem_alloc(1000);
    std::cout << location << std::endl;
    std::cout << std::endl;
    allocator.mem_dump();
    std::cout << std::endl;

    allocator.mem_realloc(location, 16);
    allocator.mem_dump();
    std::cout << std::endl;

    allocator.mem_free(location);
    allocator.mem_dump();
    std::cout << std::endl;

    allocator.mem_alloc(64);
    allocator.mem_dump();
    std::cout << std::endl;

    allocator.mem_free();
    allocator.mem_dump();
    std::cout << std::endl;
}

void test2()
{
    Allocator allocator = Allocator(1024);
    void *location1 = allocator.mem_alloc(900);
    void *location2 = allocator.mem_alloc(40);
    void *location3 = allocator.mem_alloc(20);
    allocator.mem_dump();
    allocator.mem_free(location3);
    allocator.mem_realloc(location1, 920);
    allocator.mem_dump();
}

int main() {
    try
    {
        test2();
    }
    catch (std::exception ex)
    {
        std::cerr << "error: " << ex.what() << std::endl;
        return 1;
    }
    return 0;
}
