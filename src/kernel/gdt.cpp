/*
GDT managment
Gets its own file because it needs to be compiled for 16-bit mode
*/

typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

struct FlagsLimit {
    uint8_t limit : 4;
    uint8_t flags : 4;
};

struct GDTEntry32
{
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_medium;
    uint8_t access_byte;
    FlagsLimit flags_limit;
    uint8_t base_high;
};

extern "C" void _setup_GDT( void )
{
    volatile GDTEntry32 *GDT_Table = (volatile GDTEntry32*) 0x5000;

    // Kernel Mode Code Segment
    GDT_Table[1].limit = 0xFFFF;
    GDT_Table[1].access_byte = 0x9A;
    GDT_Table[1].flags_limit.flags = 0xC;
    GDT_Table[1].flags_limit.limit = 0xF;

    // Kernel Mode Data Segment
    GDT_Table[2].limit = 0xFFFF;
    GDT_Table[2].access_byte = 0x92;
    GDT_Table[2].flags_limit.flags = 0xC;
    GDT_Table[2].flags_limit.limit = 0xF;
}