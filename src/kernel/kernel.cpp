/*
Kernel Main File
Contains entry point
*/
#include "kernel.hpp"

void KeyboardHandler( char scanCode )
{
    KeyInput input = translateScanCode(scanCode);
    
    if (input.action == KeyDown)
        term->printChr(input.key);
}

extern "C" void _start( void )
{
    InitializeHeap(0xC000);
    setup_idt();
    
    term = (VBETerminal*) calloc(sizeof(VBETerminal));
    term->clear_screen();
    term->info("Kernel Loaded!");
}