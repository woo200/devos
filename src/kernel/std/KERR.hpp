#pragma once

#include "../../types.hpp"
#include "std.hpp"

extern void KeyboardHandler( char scanCode );

#define Nop() {_asm nop _endasm}
#pragma once

#define FOREGROUND_BLACK 0x00
#define FOREGROUND_BLUE 0x01
#define FOREGROUND_GREEN 0x02
#define FOREGROUND_CYAN 0x03
#define FOREGROUND_RED 0x04
#define FOREGROUND_MAGENTA 0x05
#define FOREGROUND_BROWN 0x06
#define FOREGROUND_LIGHTGRAY 0x07
#define FOREGROUND_DARKGRAY 0x08
#define FOREGROUND_LIGHTBLUE 0x09
#define FOREGROUND_LIGHTGREEN 0x0a
#define FOREGROUND_LIGHTCYAN 0x0b
#define FOREGROUND_LIGHTRED 0x0c
#define FOREGROUND_LIGHTMAGENTA 0x0d
#define FOREGROUND_YELLOW 0x0e
#define FOREGROUND_WHITE 0x0f

#define BACKGROUND_BLACK 0x00
#define BACKGROUND_BLUE 0x10
#define BACKGROUND_GREEN 0x20
#define BACKGROUND_CYAN 0x30
#define BACKGROUND_RED 0x40
#define BACKGROUND_MAGENTA 0x50
#define BACKGROUND_BROWN 0x60
#define BACKGROUND_LIGHTGRAY 0x70
#define BACKGROUND_BLINKINGBLACK 0x80
#define BACKGROUND_BLINKINGBLUE 0x90
#define BACKGROUND_BLINKINGGREEN 0xA0
#define BACKGROUND_BLINKINGCYAN 0xB0
#define BACKGROUND_BLINKINGRED 0xC0
#define BACKGROUND_BLINKINGMAGENTA 0xD0
#define BACKGROUND_BLINKINGYELLOW 0xE0
#define BACKGROUND_BLINKINGWHITE 0xF0
#define VGA_MEMORY (uint8_t*) 0xb8000
#define VGA_WIDTH 80

namespace kstd
{
  /**
   * @brief Holds state of registers
   * 
   */
  struct registers
  {
    uint64_t rax;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rbx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rsp;
    uint64_t rbp;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;
    uint64_t r11;
    uint64_t r12;
    uint64_t r13;
    uint64_t r14;
    uint64_t r15;
  };

  void __error(char* error);
  registers dump_regs();
}