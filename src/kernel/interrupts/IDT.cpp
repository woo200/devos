#include "IDT.hpp"

extern IDT64 _idt[256];

extern uint64_t isr1;
extern uint64_t isr_df;

extern "C" void LoadIDT();

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01

/**
 * @brief Remap the PIC chip
 * 
 */
void RemapPic(){
    uint8_t a1, a2;

    a1 = inb(PIC1_DATA);
    a2 = inb(PIC2_DATA);

    outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
    outb(PIC1_DATA, 0);
    outb(PIC2_DATA, 8);
    outb(PIC1_DATA, 4);
    outb(PIC2_DATA, 2);
    outb(PIC1_DATA, ICW4_8086);
    outb(PIC2_DATA, ICW4_8086);

    outb(PIC1_DATA, a1);
    outb(PIC2_DATA, a2);

}

extern "C" void isr1_handler(){
	uint8_t scanCode = inb(0x60);

	outb(0x20, 0x20);
	outb(0xa0, 0x20);
}

void write_string( int colour, const char *string )
{
    volatile char *video = (volatile char*)0xB8000;
    while( *string != 0 )
    {
        *video++ = *string++;
        *video++ = colour;
    }
}

extern "C" void DF_handler() {
    volatile char *video = (volatile char*)0xB8000;
    for (int i = 0; i < 80*25; i++)
    {
        *video++ = ' ';
        *video++ = 0;
    }
    kstd::__error("UNRECOVERABLE: Double Fault Detected");
    for (;;) { asm("hlt"); }
}

void setup_idt(){    
    _idt[1].zero = 0;
    _idt[1].offset_low = (uint16_t)(((uint64_t)0xFFF & 0x000000000000ffff));
    _idt[1].offset_mid = (uint16_t)(((uint64_t)&isr1 & 0x00000000ffff0000) >> 16);
    _idt[1].offset_high = (uint32_t)(((uint64_t)&isr1 & 0xffffffff00000000) >> 32);
    _idt[1].ist = 0;
    _idt[1].selector = 0x08;
    _idt[1].types_attr = 0x8E;

    _idt[0x8].zero = 0;
    _idt[0x8].offset_low = (uint16_t)(((uint64_t)&isr_df & 0x000000000000ffff));
    _idt[0x8].offset_mid = (uint16_t)(((uint64_t)&isr_df & 0x00000000ffff0000) >> 16);
    _idt[0x8].offset_high = (uint32_t)(((uint64_t)&isr_df & 0xffffffff00000000) >> 32);
    _idt[0x8].ist = 0;
    _idt[0x8].selector = 0x08;
    _idt[0x8].types_attr = 0x8F;

	RemapPic();

	outb(0x21, 0xfd);
	outb(0xa1, 0xff);
	LoadIDT();
}