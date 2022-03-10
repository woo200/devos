#include "IDT.hpp"

extern IDT64 _idt[256];
extern uint64_t isr1;
extern "C" void LoadIDT();

#define PIC1_COMMAND 0x20
#define PIC1_DATA 0x21
#define PIC2_COMMAND 0xA0
#define PIC2_DATA 0xA1

#define ICW1_INIT 0x10
#define ICW1_ICW4 0x01
#define ICW4_8086 0x01

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
	// uint8_t scanCode = inb(0x60);
	// outb(0x20, 0x20);
	// outb(0xa0, 0x20);
    while (true) {}
}

void setup_idt(){
    // TODO: IDT Causes GPF whenever an interrupt is triggered
    _idt[0].zero = 0;
    _idt[0].offset_low = (uint16_t)(((uint64_t)&isr1 & 0x000000000000ffff));
    _idt[0].offset_mid = (uint16_t)(((uint64_t)&isr1 & 0x00000000ffff0000) >> 16);
    _idt[0].offset_high = (uint32_t)(((uint64_t)&isr1 & 0xffffffff00000000) >> 32);
    _idt[0].ist = 0;
    _idt[0].selector = 0x08;
    _idt[0].types_attr = 0x8F;

	RemapPic();

	outb(0x21, 0xfd);
	outb(0xa1, 0xff);
	LoadIDT();
}