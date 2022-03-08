/*
Kernel Main File
Contains entry point
*/

#include "types.hpp";

void _setup_paging( uint64_t* _PML4_table )
{

}

extern "C" void _setup_PML4( void )
{
    uint64_t* _PML4_address = (uint64_t*) 0xC000; // idek
    _setup_paging(_PML4_address);
}

extern "C" void _start( void )
{

}