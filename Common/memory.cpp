#include "memory.hpp"


void* operator new(size_t size) noexcept {
    return pvPortMalloc(size);
}

void operator delete(void* ptr) noexcept {
    vPortFree(ptr);
}

