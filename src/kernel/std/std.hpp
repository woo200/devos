#pragma once

#include "../../types.hpp"

struct MemorySegment {
    uint64_t size;
    bool isFree;
    MemorySegment* nextSeg;
    MemorySegment* prevSeg;
    MemorySegment* nextFreeSeg;
    MemorySegment* prevFreeSeg;
};

void InitializeHeap(uint64_t HeapStart);

void* malloc(uint64_t size);
void* calloc(uint64_t size);

void free(void* mem_seg);