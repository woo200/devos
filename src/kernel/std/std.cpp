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
    if (LargestFreeMemorySeg && LargestFreeMemorySeg->size >= requestedMemorySize)
    {
        MemorySegment* AllocatedMemorySegment = LargestFreeMemorySeg;

        AllocatedMemorySegment->isFree = false;

        if (AllocatedMemorySegment->nextSeg)
            AllocatedMemorySegment->nextSeg->prevFreeSeg = AllocatedMemorySegment->prevFreeSeg ? AllocatedMemorySegment->prevFreeSeg : 0;
        if (AllocatedMemorySegment->prevSeg)
            AllocatedMemorySegment->prevSeg->nextFreeSeg = AllocatedMemorySegment->nextFreeSeg ? AllocatedMemorySegment->nextFreeSeg : 0;

        MemorySegment* SegIterator = LastMemorySeg->isFree ? LastMemorySeg : LastMemorySeg->prevFreeSeg;
        LargestFreeMemorySeg = 0;

        while (SegIterator) {
            if (!LargestFreeMemorySeg || SegIterator->size > LargestFreeMemorySeg->size)
                LargestFreeMemorySeg = SegIterator;
            SegIterator = SegIterator->prevFreeSeg;
        }

        return ((void*) AllocatedMemorySegment) + sizeof(MemorySegment);
    }
    
    // Allocate a new memory segment
    MemorySegment* NewMemorySegment = LastMemorySeg + LastMemorySeg->size + sizeof(MemorySegment);

    NewMemorySegment->size = requestedMemorySize;
    NewMemorySegment->isFree = false;
    NewMemorySegment->prevSeg = LastMemorySeg;
    NewMemorySegment->nextSeg = 0;
    NewMemorySegment->nextFreeSeg = 0;
    NewMemorySegment->prevFreeSeg = LastMemorySeg->prevFreeSeg;

    LastMemorySeg->nextSeg = NewMemorySegment;
    LastMemorySeg = NewMemorySegment;

    return ((void*) NewMemorySegment) + sizeof(MemorySegment);
}

void* calloc(uint64_t requestedMemorySize)
{
    void* memory = malloc(requestedMemorySize);
    for (int i = 0; i < requestedMemorySize; i++)
        *((char*) (memory + i)) = 0;
    return memory;
}

void free(void* segToFree)
{
    MemorySegment* memSeg = (MemorySegment*) (segToFree - sizeof(MemorySegment));
    memSeg->isFree = true;
    
    // If next segment is free, merge the two
    if (memSeg->nextSeg && memSeg->nextSeg->isFree) {
        memSeg->size += sizeof(MemorySegment) + memSeg->nextSeg->size; // Set this segments size to the size of the seg next to it

        memSeg->nextSeg->nextSeg->prevSeg = memSeg; // Set the seg after the merged seg's prev seg to this seg
        memSeg->nextSeg->nextSeg->prevFreeSeg = memSeg; // Set the seg after the merged seg's prev free seg to this 

        memSeg->nextSeg = memSeg->nextSeg->nextSeg; // Set next seg to the seg after the merged seg
        memSeg->nextFreeSeg = memSeg->nextSeg->nextFreeSeg; // set next free seg to next free seg after merged seg
    }

    if (!LargestFreeMemorySeg || memSeg->size > LargestFreeMemorySeg->size)
        LargestFreeMemorySeg = memSeg;

    memSeg->prevSeg->nextFreeSeg = memSeg;
}

VBETerminal::VBETerminal()
{
    this->currentPos = 0;
}

void VBETerminal::print(int colour, const char *string)
{
    volatile char *video = (volatile char*)0xB8000 + (this->currentPos * 2);
    while( *string != 0 )
    {
        if (*string == '\n') {
            int charsLeft = 80 - (this->currentPos % 80);

            video += charsLeft * 2;
            currentPos += charsLeft;

            string++;
            continue;
        }
        *video++ = *string++;
        *video++ = colour;
        this->currentPos++;
    }
}

void VBETerminal::print(const char *string)
{
    this->print(0xF, string);
}

void VBETerminal::println(int color, const char *string)
{
    this->print(color, string);
    this->print(0x0, "\n");
}

void VBETerminal::println(const char *string)
{
    this->println(0xF, string);
}

void VBETerminal::clear_screen()
{
    volatile char *video = (volatile char*)0xB8000;
    for (int i = 0; i < 80*25; i++)
    {
        *video++ = ' ';
        *video++ = 0;
    }
}

void VBETerminal::printHex(int color, uint64_t value)
{
    char hexchars[] = "0123456789ABCDEF";
    char text_to_print[19];

    text_to_print[0] = '0';
    text_to_print[1] = 'x';

    for (int i = 0; i < 16; i++) {
        int current_chr = value >> i * 4 & 0xF;
        text_to_print[15-i+2] = hexchars[current_chr];
    }
    text_to_print[18] = '\0';

    this->print(color, text_to_print);
}

void VBETerminal::printHex(uint64_t value)
{
    this->printHex(0xF, value);
}

void VBETerminal::info( const char *message )
{
    this->print(0xF, "[ KERNEL ] ");
    this->println(0xA, message);
}

int strlen(const char *str)
{
    int result = 0;
    while (*str)
    {
        result++;
        str++;
    }
    return result;
}

void strcpy(const char *cStr, char *cpyStr)
{
    while (*cStr)
    {
        *cpyStr = *cStr++;
    }
}