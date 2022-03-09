#pragma once

#include "../../types.hpp"
#include "string.hpp"

struct MemorySegment {
    uint64_t size;
    bool isFree;
    MemorySegment* nextSeg;
    MemorySegment* prevSeg;
    MemorySegment* nextFreeSeg;
    MemorySegment* prevFreeSeg;
};

class VBETerminal {
    int currentPos;
public:
    VBETerminal();

    void print( int color, const char *string );
    void print( const char *string );

    void println( int color, const char *string );
    void println( const char *string );

    void printHex( uint64_t value );
    void printHex( int color, uint64_t value );

    void info( const char *string );

    void clear_screen();
};

void InitializeHeap(uint64_t HeapStart);

void* malloc(uint64_t size);
void* calloc(uint64_t size);
void* realloc(void* oldMem, uint64_t size);

void memcpy(void* source, void* destination, int size);

int strlen(const char *cStr);
char* strcpy(const char *source, char *destination);
char* strcat(char* destination, const char* source);

void free(void* mem_seg);