#pragma once

#include "../../types.hpp"
#include "string.hpp"

/**
 * @brief Header to all memory blocks
 */
struct MemorySegment {
    uint64_t size;              /**< Size of memory segment */
    bool isFree;                /**< Is the segment free? */
    MemorySegment* nextSeg;     /**< Next Memory Segment */
    MemorySegment* prevSeg;     /**< Previous Memory Segment */
    MemorySegment* nextFreeSeg; /**< Next Free Memory Segment */
    MemorySegment* prevFreeSeg; /**< Previous Free Memory Segment */
};

/**
 * @brief Control the terminal
 * 
 */
class VBETerminal {
    int currentPos;
public:
    VBETerminal();

    void print( int color, const char *string );
    void print( const char *string );

    void printChr(int color, char chr);
    void printChr( char chr );

    void println( int color, const char *string );
    void println( const char *string );

    void printHex( uint64_t value );
    void printHex( int color, uint64_t value );

    void moveCursor( uint8_t cursorPos );
    uint8_t getCursorPos();

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
int strcmp(const char *X, const char *Y);

void free(void* mem_seg);

void outb(unsigned short port, unsigned char val);
void outbyte(unsigned short port, unsigned char val);
unsigned char inb(unsigned short port);
