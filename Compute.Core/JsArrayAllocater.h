
#pragma once

#include "RasterCore.h"

class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator
{
public:
    ArrayBufferAllocator() = default;
    ~ArrayBufferAllocator() = default;

    void * AllocateUninitialized(size_t length) override;
    void * Allocate(size_t length) override;

    void Free(void* data, size_t) override;
};
