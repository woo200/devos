/*
Kernel Main File
Contains entry point
*/
#include "kernel.hpp"

KeyInput lastKbInput;
bool kbByteAvailable;

void KeyboardHandler( char scanCode )
{
    KeyInput input = translateScanCode(scanCode);
    
    lastKbInput = input;
    kbByteAvailable = true;
}

KeyInput getKey()
{
    while (!kbByteAvailable) { }
    kbByteAvailable = false;
    return lastKbInput;
}

std::string input()
{
    std::string str;
    while (true) {
        KeyInput input = getKey();
        if (input.action == KeyUp) continue; 
        if (input.key == Enter) break;
        if (input.key == Backspace) {
            free(str.pop(1));
            term->moveCursor(term->getCursorPos() - 1);
            term->printChr(' ');
            term->moveCursor(term->getCursorPos() - 1);
            continue;
        }
        char key = translateKeyCode(input.key);
        if (key == 0) continue;
        term->printChr(key);
        str += key; 
    }
    return str;
}

extern "C" void _start( void )
{
    InitializeHeap(0xC000);
    setup_idt();
    
    term = (VBETerminal*) calloc(sizeof(VBETerminal));
    term->clear_screen();
    term->info("Kernel Loaded!");
    
    // while (true) {
    //     term->print("> ");
    //     std::string testStr = input();
    //     if (testStr == "CLS") {
    //         term->clear_screen();
    //         term->moveCursor(0);
    //         term->println("Screen Cleared");
    //         continue;
    //     }
    //     if (testStr == "RESET KERNEL") {
    //         term->moveCursor(0);
    //         term->println("Reseting Kernel");
    //         _start();
    //         break;
    //     }
    //     term->println("\nUnknown Command. Type HELP for help.");
    // }
    while (true) {
        
    }
}