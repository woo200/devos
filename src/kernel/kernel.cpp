/*
Kernel Main File
Contains entry point
*/

#include "../types.hpp"
#include "std/std.hpp"

int currentPos = 0;

void write_string( int colour, const char *string )
{
    volatile char *video = (volatile char*)0xB8000 + (currentPos*2);
    while( *string != 0 )
    {
        if (*string == '\n') {
            int charsLeft = 80 - (currentPos % 80);

            video += charsLeft * 2;
            currentPos += charsLeft;

            string++;
            continue;
        }
        *video++ = *string++;
        *video++ = colour;
        currentPos++;
    }
}

void clear_screen()
{
    volatile char *video = (volatile char*)0xB8000;
    for (int i = 0; i < 80*25; i++)
    {
        *video++ = ' ';
        *video++ = 0;
    }
}

void print_hex( uint64_t value )
{
    char hexchars[] = "0123456789ABCDEF";
    char text_to_print[19];

    text_to_print[0] = '0';
    text_to_print[1] = 'x';

    for (int i = 0; i < 16; i++) {
        int current_chr = value >> i * 4 & 0xF;
        text_to_print[15-i+2] = hexchars[current_chr];
    }
    text_to_print[18] = '\0';

    write_string(2, text_to_print);
}

extern "C" void _start( void )
{
    clear_screen();
    print_hex((uint64_t)0xDEADBEEFDEADBEEF);
    write_string(02, "\nHello, World!");
}