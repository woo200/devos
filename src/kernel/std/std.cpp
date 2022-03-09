#include "std.hpp"

MemorySegment* LastMemorySeg;
MemorySegment* LargestFreeMemorySeg;

void InitializeHeap(uint64_t HeapStart) {
    MemorySegment* FirstMemorySegment = (MemorySegment*) HeapStart;

    FirstMemorySegment->size = 0;
    FirstMemorySegment->isFree = false; // Reserved
    FirstMemorySegment->nextSeg = 0;
    FirstMemorySegment->prevSeg = 0;
    FirstMemorySegment->nextFreeSeg = 0;
    FirstMemorySegment->prevFreeSeg = 0;

    LastMemorySeg = FirstMemorySegment;
    LargestFreeMemorySeg = FirstMemorySegment;
}

void* malloc(uint64_t requestedMemorySize)
{
    // There is an existing free memory segment that can fit the requested value
    if (LargestFreeMemorySeg->size >= requestedMemorySize) {
        MemorySegment* AllocatedMemorySegment = LargestFreeMemorySeg;
        LargestFreeMemorySeg->isFree = false;
        
        LargestFreeMemorySeg->prevSeg->nextFreeSeg = LargestFreeMemorySeg->nextFreeSeg;
        if (LargestFreeMemorySeg->nextSeg)
            LargestFreeMemorySeg->nextSeg->prevFreeSeg = LargestFreeMemorySeg->prevFreeSeg;
        
        LargestFreeMemorySeg = LargestFreeMemorySeg->prevFreeSeg;
        MemorySegment* MemSeg = LastMemorySeg;
        if (!MemSeg->isFree)
            MemSeg = MemSeg->prevFreeSeg;

        while (MemSeg)
        {
            if (MemSeg->size > LargestFreeMemorySeg->size)
                LargestFreeMemorySeg = MemSeg;
            MemSeg = MemSeg->prevFreeSeg;
        }
        return AllocatedMemorySegment + sizeof(AllocatedMemorySegment);
    }
    
    // Allocate a new memory segment
    MemorySegment* NewMemorySegment = LastMemorySeg + sizeof(MemorySegment) + LastMemorySeg->size;
    NewMemorySegment->size = requestedMemorySize;
    NewMemorySegment->isFree = false;
    NewMemorySegment->prevSeg = LastMemorySeg;
    NewMemorySegment->nextSeg = 0;
    NewMemorySegment->nextFreeSeg = 0;
    NewMemorySegment->prevFreeSeg = LastMemorySeg->prevFreeSeg;

    LastMemorySeg->nextSeg = NewMemorySegment;
    LastMemorySeg = NewMemorySegment;

    return NewMemorySegment;
}

void* calloc(uint64_t requestedMemorySize)
{
    void* memory = malloc(requestedMemorySize);
    for (int i = 0; i < requestedMemorySize; i++)
        *((char*) (memory + i)) = 0;
    return memory;
}

void free(void* mem_seg)
{
    MemorySegment* memSeg = (MemorySegment*) mem_seg - sizeof(MemorySegment);
    memSeg->isFree = true;
    
    // If next segment is free, merge the two
    if (memSeg->nextSeg && memSeg->nextSeg->isFree)
        memSeg->size += sizeof(MemorySegment) + memSeg->nextSeg->size; // Set this segments size to the size of the seg next to it

        memSeg->nextSeg->nextSeg->prevSeg = memSeg; // Set the seg after the merged seg's prev seg to this seg
        memSeg->nextSeg->nextSeg->prevFreeSeg = memSeg; // Set the seg after the merged seg's prev free seg to this 

        memSeg->nextSeg = memSeg->nextSeg->nextSeg; // Set next seg to the seg after the merged seg
        memSeg->nextFreeSeg = memSeg->nextSeg->nextFreeSeg; // set next free seg to next free seg after merged seg
    
    if (memSeg->size > LargestFreeMemorySeg->size)
        LargestFreeMemorySeg = memSeg;

    memSeg->prevSeg->nextFreeSeg = memSeg;
}