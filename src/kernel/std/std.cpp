#include "std.hpp"

MemorySegment* LastMemorySeg;
MemorySegment* LargestFreeMemorySeg;

/**
 * @brief Initialzie the heap to a memory address
 * 
 * @param HeapStart Memory address to start heap
 */
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

/**
 * @brief Allocate memory
 * 
 * @param requestedMemorySize How much memory to allocate
 * @return void* Allocated memory
 */
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

/**
 * @brief Allocate memory and initialize it to zero
 * 
 * @param requestedMemorySize Requested memory size
 * @return void* Allocated memory
 */
void* calloc(uint64_t requestedMemorySize)
{
    void* memory = malloc(requestedMemorySize);
    for (int i = 0; i < requestedMemorySize; i++)
        *((char*) (memory + i)) = 0;
    return memory;
}

/**
 * @brief Reallocate a memory segment to make it bigger
 * 
 * @param oldMem Old memory address
 * @param requestedMemorySize New memory size
 * @return void* Reallocated memory
 */
void* realloc(void* oldMem, uint64_t requestedMemorySize)
{
    void* newMemory = (void*)calloc(requestedMemorySize);
    MemorySegment* memSeg = (MemorySegment*) (oldMem - sizeof(MemorySegment));
    memcpy(oldMem, newMemory, memSeg->size);
    return newMemory;
}

/**
 * @brief Copy memory
 * 
 * @param src Source memory address
 * @param dest Destination memory address
 * @param size Number of bytes to copy
 */
void memcpy(void* src, void* dest, int size)
{
    char *csrc = (char *)src;
    char *cdest = (char *)dest;
    
    for (int i=0; i<size; i++)
        cdest[i] = csrc[i];
}

/**
 * @brief Free memory
 * 
 * @param segToFree Segment to free
 */
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

/**
 * @brief Construct a new VBETerminal::VBETerminal object
 * 
 */
VBETerminal::VBETerminal()
{
    this->currentPos = 0;
}

/**
 * @brief Print colored string to terminal
 * 
 * @param colour color
 * @param string string to print
 */
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

/**
 * @brief Print a string to terminal
 * 
 * @param string string to print
 */
void VBETerminal::print(const char *string)
{
    this->print(0xF, string);
}

/**
 * @brief Print a colored string and newline to the terminal
 * 
 * @param color color
 * @param string string to print
 */
void VBETerminal::println(int color, const char *string)
{
    this->print(color, string);
    this->print(0x0, "\n");
}

/**
 * @brief Print a string and newline to the terminal
 * 
 * @param string string to print
 */
void VBETerminal::println(const char *string)
{
    this->println(0xF, string);
}

/**
 * @brief Print char to screen
 * 
 * @param color Color
 * @param chr Char to print
 */
void VBETerminal::printChr(int color, char chr)
{
    if (chr == '\n') {
        int charsLeft = 80 - (this->currentPos % 80);
        currentPos += charsLeft;
        return;
    }

    volatile char *video = (volatile char*)0xB8000 + (this->currentPos * 2);
    *video++ = chr;
    *video = color;
    this->currentPos++;
}

/**
 * @brief Print char to screen
 * 
 * @param chr Char to print
 */
void VBETerminal::printChr(char chr)
{
    this->printChr(0xF, chr);
}

/**
 * @brief Clear the screen
 * 
 */
void VBETerminal::clear_screen()
{
    volatile char *video = (volatile char*)0xB8000;
    for (int i = 0; i < 80*25; i++)
    {
        *video++ = ' ';
        *video++ = 0;
    }
}

/**
 * @brief Move cursor to position
 * 
 * @param cursorPos cursor position
 */
void VBETerminal::moveCursor( uint8_t cursorPos )
{
    this->currentPos = cursorPos;
}

/**
 * @brief Get cursor position
 * 
 * @return uint8_t current position of cursor
 */
uint8_t VBETerminal::getCursorPos()
{
    return this->currentPos;
}

/**
 * @brief Print colored hex value to screen
 * 
 * @param color color
 * @param value value to print
 */
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

/**
 * @brief Print hex value to screen
 * 
 * @param value value to print
 */
void VBETerminal::printHex(uint64_t value)
{
    this->printHex(0xF, value);
}

/**
 * @brief Log info to kernel screen
 * 
 * @param message message to print
 */
void VBETerminal::info( const char *message )
{
    this->print(0xF, "[ KERNEL ] ");
    this->println(0xA, message);
}

/**
 * @brief Get the length of a C string
 * 
 * @param str string
 * @return int Length of {@code string}
 */
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

/**
 * @brief Compare two C strings
 * 
 * @param X String 1
 * @param Y String 2
 * @return int ASCII difference between strings
 */
int strcmp(const char *X, const char *Y)
{
    while (*X)
    {
        if (*X != *Y) {
            break;
        }
        X++;
        Y++;
    }
 
    // return the ASCII difference after converting `char*` to `unsigned char*`
    return *(const unsigned char*)X - *(const unsigned char*)Y;
}

/**
 * @brief Copy a string 
 * 
 * @param source Source string
 * @param destination Destination string
 * @return char* address of {@destination}
 */
char* strcpy(const char* source, char* destination)
{
    char *ptr = destination;
    while (*source != '\0')
    {
        *destination = *source;
        destination++;
        source++;
    }
     *destination = '\0';
     return ptr;
}

/**
 * @brief Concatenate two C strings
 * 
 * @param destination Base string
 * @param source String to concat to base
 * @return char* address of {@code destination}
 */
char* strcat(char* destination, const char* source)
{
    char* ptr = destination + strlen(destination);
     while (*source != '\0') {
        *ptr++ = *source++;
    }
    *ptr = '\0';
    return destination;
}

/**
 * @brief Write a byte to a port
 * 
 * @param port Port
 * @param val Value
 */
void outb(unsigned short port, unsigned char val){
  asm volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

/**
 * @brief Write a byte to a port
 * 
 * @param port Port
 * @param val Value
 */
void outbyte(unsigned short port, unsigned char val) {
    outb(port, val);
}

/**
 * @brief Get a byte from a port
 * 
 * @param port Port
 * @return unsigned char Byte
 */
unsigned char inb(unsigned short port){
  unsigned char returnVal;
  asm volatile ("inb %1, %0"
  : "=a"(returnVal)
  : "Nd"(port));
  return returnVal;
}