#include "KERR.hpp"

namespace kstd
{
  void __error(char* error)
  {
    kstd::ClearScreen(BACKGROUND_RED | FOREGROUND_WHITE);
    kstd::setCursorPosition(kstd::positionFromCoords(VGA_WIDTH / 2 - 9, 2));
    kstd::PrintString("FATAL KERNEL ERROR", BACKGROUND_BLINKINGRED | FOREGROUND_WHITE);
    kstd::setCursorPosition(kstd::positionFromCoords(VGA_WIDTH / 2 - (strlen(error) / 2), 4));
    kstd::PrintStringwNLCenter(error, BACKGROUND_RED | FOREGROUND_WHITE);
    kstd::PrintString("\n\n");

    std::string rip("RAX=");
    registers reg = dump_regs();

    kstd::setCursorPosition(cursorPosition - (cursorPosition % VGA_WIDTH) + 1);

    rip += kstd::hexToString(reg.rbp);

    kstd::PrintString(rip.cStr(), BACKGROUND_RED | FOREGROUND_WHITE);

    kstd::setCursorPosition(kstd::positionFromCoords(VGA_WIDTH, 50));

    int i = 0;
    bool state = true;

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
