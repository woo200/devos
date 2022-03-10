#include "KERR.hpp"

namespace kstd
{
  void ClearScreen(uint64_t ClearColor)
  {
    uint64_t value = 0;

    value += ClearColor << 8;
    value += ClearColor << 24;
    value += ClearColor << 40;
    value += ClearColor << 56;

    for (uint64_t* i = (uint64_t*)VGA_MEMORY; i < (uint64_t*)(VGA_MEMORY + 4000); ++i)
    {
      *i = value;
    }
  }

  uint16_t positionFromCoords(uint8_t x, uint8_t y)
  {
    return y * VGA_WIDTH + x;
  }

  void PrintString(const char* str, uint8_t color, uint16_t position)
  {
    uint8_t* charPtr = (uint8_t*)str;

    while (*charPtr != 0)
    {
      switch (*charPtr)
      {
        case 10:
          position += VGA_WIDTH;
        case 13:
          position -= position % VGA_WIDTH;
          break;
        default:
          *(VGA_MEMORY + position * 2) = *charPtr;
          *(VGA_MEMORY + position * 2 + 1) = color;
          ++position;
      }
      ++charPtr;
    }
  }

  void printHex(uint64_t value, uint16_t color, uint16_t position)
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

      PrintString(text_to_print, color, position);
  }

  void printRegister(uint64_t value, char* reg, int x, int y)
  {
    int pos = kstd::positionFromCoords(3 + (25 * x), y);
    kstd::PrintString(reg, BACKGROUND_RED | FOREGROUND_WHITE, pos);
    pos += 5;
    kstd::printHex(value, BACKGROUND_RED | FOREGROUND_WHITE, pos);
  }

  void __error(char* error)
  {
    kstd::ClearScreen(BACKGROUND_RED | FOREGROUND_WHITE);
    kstd::PrintString("FATAL KERNEL ERROR", BACKGROUND_BLINKINGRED | FOREGROUND_WHITE, kstd::positionFromCoords(VGA_WIDTH / 2 - 9, 3));
    kstd::PrintString(error, BACKGROUND_RED | FOREGROUND_WHITE, kstd::positionFromCoords(VGA_WIDTH / 2 - (strlen(error) / 2), 5));

    registers reg = dump_regs();
    printRegister(reg.rax, "RAX:", 0, 7);
    printRegister(reg.rbx, "RBX:", 1, 7);
    printRegister(reg.rcx, "RCX:", 2, 7);
    printRegister(reg.rdx, "RDX:", 0, 8);
    printRegister(reg.rsi, "RSI:", 1, 8);
    printRegister(reg.rdi, "RDI:", 2, 8);
    printRegister(reg.rbp, "RBP:", 0, 9);
    printRegister(reg.rsp, "RSP:", 1, 9);
    printRegister(reg.r8, "R8:", 0, 11);
    printRegister(reg.r9, "R9:", 1, 11);
    printRegister(reg.r10, "R10:", 2, 11);
    printRegister(reg.r11, "R11:", 0, 12);
    printRegister(reg.r12, "R12:", 1, 12);
    printRegister(reg.r13, "R13:", 2, 12);
    printRegister(reg.r14, "R14:", 0, 13);
    printRegister(reg.r15, "R15:", 1, 13);
    while (1) { }
  }

  registers dump_regs()
  {
    registers reg;

    __asm__
    __volatile__
    (
      "mov %%rax, %[output]"
      : [output] "=r" (reg.rax)
    );
    __asm__
    __volatile__
    (
      "mov %%rcx, %[output]"
      : [output] "=r" (reg.rcx)
    );
    __asm__
    __volatile__
    (
      "mov %%rdx, %[output]"
      : [output] "=r" (reg.rdx)
    );
    __asm__
    __volatile__
    (
      "mov %%rbx, %[output]"
      : [output] "=r" (reg.rbx)
    );
    __asm__
    __volatile__
    (
      "mov %%rsi, %[output]"
      : [output] "=r" (reg.rsi)
    );
    __asm__
    __volatile__
    (
      "mov %%rdi, %[output]"
      : [output] "=r" (reg.rdi)
    );
    __asm__
    __volatile__
    (
      "mov %%rsp, %[output]"
      : [output] "=r" (reg.rsp)
    );
    __asm__
    __volatile__
    (
      "mov %%rbp, %[output]"
      : [output] "=r" (reg.rbp)
    );
    __asm__
    __volatile__
    (
      "mov %%r8, %[output]"
      : [output] "=r" (reg.r8)
    );
    __asm__
    __volatile__
    (
      "mov %%r9, %[output]"
      : [output] "=r" (reg.r9)
    );
    __asm__
    __volatile__
    (
      "mov %%r10, %[output]"
      : [output] "=r" (reg.r10)
    );
    __asm__
    __volatile__
    (
      "mov %%r11, %[output]"
      : [output] "=r" (reg.r11)
    );
    __asm__
    __volatile__
    (
      "mov %%r12, %[output]"
      : [output] "=r" (reg.r12)
    );
    __asm__
    __volatile__
    (
      "mov %%r13, %[output]"
      : [output] "=r" (reg.r13)
    );
    __asm__
    __volatile__
    (
      "mov %%r14, %[output]"
      : [output] "=r" (reg.r14)
    );
    __asm__
    __volatile__
    (
      "mov %%r15, %[output]"
      : [output] "=r" (reg.r15)
    );

    return reg;
  }
}
