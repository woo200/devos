/*
Kernel Main File
Contains entry point
*/
#include "../types.hpp"
#include "std/std.hpp"
#include "./interrupts/IDT.hpp"

extern IDT64 _idt[256];

extern "C" void _start( void )
{
    InitializeHeap(0xC000);
    setup_idt();
    
    VBETerminal* term = (VBETerminal*) calloc(sizeof(VBETerminal));

    term->clear_screen();
    term->info("Kernel Started");

    std::string test("Hello, World!");
    term->info(test.cStr());
    term->printHex((uint64_t)&_idt[1]);
}