
#pragma once

#include "RasterCore.h"

class ArrayBufferAllocator : public v8::ArrayBuffer::Allocator
{
public:
    void * Allocate(size_t length) override {
        auto data = AllocateUninitialized(length);
        return data == nullptr ? data : memset(data, 0, length);
    }

    void * AllocateUninitialized(size_t length) override {
        return malloc(length);
    }

    void Free(void* data, size_t) override {
        free(data);
    }
};
