/*
Kernel Main File
Contains entry point
*/

#include "../types.hpp"
#include "std/std.hpp"

extern "C" void _start( void )
{
    InitializeHeap(0xC000);
    
    VBETerminal* term = (VBETerminal*) calloc(sizeof(VBETerminal));
    
    term->clear_screen();
    term->info("Kernel Started");
}