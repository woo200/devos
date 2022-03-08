/*
Kernel Main File
Contains entry point
*/

#include "../types.hpp"
void write_string( int colour, const char *string )
{
    volatile char *video = (volatile char*)0xB8000;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}

extern "C" void _setup_PML4( void )
{
    // write_string(2, "HELLO");

    volatile uint64_t* _PML4_table_address = (volatile uint64_t*) 0x1000;
    volatile uint64_t* _PAGE_DIRECTORY_POINTER_TABLE = (volatile uint64_t*) 0x2000;
    volatile uint64_t* _PAGE_DIRECTORY = (volatile uint64_t*) 0x3000;
    volatile uint64_t* _PAGE_TABLE = (volatile uint64_t*) 0x4000;

    _PAGE_TABLE[0] = (1 << 0) | (1 << 1) | (0x00000000 * 4096); // Allocate a 4Kb page at 0x1064000
    _PAGE_DIRECTORY[0] = (1 << 0) | (1 << 1) | ((uint64_t) _PAGE_TABLE * 4096);
    _PAGE_DIRECTORY_POINTER_TABLE[0] = (1 << 0) | (1 << 1) | ((volatile uint64_t) _PAGE_DIRECTORY * 4096);
    _PML4_table_address[0] = (1 << 0) | (1 << 1) | (1 << 2) | ((volatile uint64_t) _PAGE_DIRECTORY_POINTER_TABLE * 4096);
}

extern "C" void _start( void )
{
    for (uint64_t i = 0xA0000; i < 0xB8000; i++) {
        *(char*)i = 256;
    }
}