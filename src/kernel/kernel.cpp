/*
Kernel Main File
Contains entry point
*/
#pragma once

#include "../types.hpp"
#include "std/std.hpp"
#include "interrupts/IDT.hpp"

VBETerminal* term;

extern "C" void _start( void )
{
    InitializeHeap(0xC000);
    setup_idt();
    
    term = (VBETerminal*) calloc(sizeof(VBETerminal));

    term->clear_screen();
    term->info("Kernel Started");

    std::string test("Hello, World!");
    term->info(test.cStr());
}