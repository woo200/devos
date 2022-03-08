[org 0x7c00]

global _start
_start:
  mov [BOOT_DISK], dl

  ; Setup stack
  mov bp, 0x7c00
  mov sp, bp

  call ReadDisk     ; Read the disk and load into memory
  jmp PROGRAM_SPACE ; Jump into the program

%include "src/bootloader/print.asm"
%include "src/bootloader/diskread.asm"

times 510-($-$$) db 0

dw 0xaa55
