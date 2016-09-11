
#include "JsArrayAllocater.h"

void * ArrayBufferAllocator::Allocate(size_t length)
{
    auto data = AllocateUninitialized(length);
    return data == nullptr ? data : memset(data, 0, length);
}

void * ArrayBufferAllocator::AllocateUninitialized(size_t length)
{
    return malloc(length);
}

void ArrayBufferAllocator::Free(void* data, size_t) 
{
    free(data);
}