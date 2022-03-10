/*
Kernel Main File
Contains entry point
*/
#include "../types.hpp"
#include "std/std.hpp"
#include "./interrupts/IDT.hpp"

extern "C" void _start( void )
{
    InitializeHeap(0xC000);
    setup_idt();
    
    VBETerminal* term = (VBETerminal*) calloc(sizeof(VBETerminal));
    term->clear_screen();
    term->info("Kernel Loaded");
    
}