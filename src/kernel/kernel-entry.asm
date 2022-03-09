jmp EnterProtectedMode

%include "src/kernel/gdt.asm"

[bits 16]
EnterProtectedMode:
    call EnableA20          ; Enable A20 Line
    cli
    lgdt [gdt_descriptor]   ; Load GDT

    mov eax, cr0 
    or al, 1                ; set PE (Protection Enable) bit in CR0 (Control Register 0)
    mov cr0, eax

    jmp codeseg:StartProtectedMode

EnableA20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

[bits 32]

%include "src/kernel/paging.asm"

StartProtectedMode:
  mov ax, dataseg

  mov ds, ax
  mov ss, ax
  mov es, ax
  mov fs, ax
  mov gs, ax

  call SetUpIdentityPaging
  call EditGDT

  jmp codeseg:Start64Bit

[bits 64]
[extern _start]
Start64Bit:
    call _start
    jmp $

    