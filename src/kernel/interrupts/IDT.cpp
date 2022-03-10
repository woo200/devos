#include "IDT.hpp"

extern IDT64 _idt[256];
extern uint64_t isr1;
extern "C" void LoadIDT();

void setup_idt( void )
{
    for (int i = 0; i < 256; i++)
    {
        _idt[i].zero = 0;
        _idt[i].offset_1 = (uint16_t) ((uint64_t)&isr1 & 0xFFFF);
        _idt[i].offset_2 = (uint16_t) (((uint64_t)&isr1 & 0xFFFF0000) >> 16);
        _idt[i].offset_2 = (uint32_t) (((uint64_t)&isr1 & 0xFFFFFFFF00000000) >> 32);
        _idt[i].ist = 0;
        _idt[i].type_attributes = 0x8E;
        _idt[i].selector = 0x08;
    }

    outb(0x21, 0xfd);
	outb(0xa1, 0xff);
	LoadIDT();
}

extern "C" void isr1_handler( void )
{
    uint8_t scanCode = inb(0x60);
    term->printHex((uint64_t) scanCode);
    term->println("");

    outb(0x20, 0x20);
    outb(0xA0, 0x20);    
}