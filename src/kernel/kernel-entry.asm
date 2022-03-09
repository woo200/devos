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

; [bits 32]
; EnablePaging:
;     ; Enable PAE
;     mov edx, cr4
;     or  edx, (1 << 5)
;     mov cr4, edx
    
;     ; Set LME (long mode enable)
;     mov ecx, 0xC0000080
;     rdmsr
;     or  eax, (1 << 8)
;     wrmsr

;     mov [0xFFFF], word 0x0200;0007
;     mov [0x2000], word 0x0300;0003
;     mov [0x3000], word 0x0400;0003
;     mov [0x4000], word 0x0600;0003
;     jmp $

;     ; Replace 'pml4_table' with the appropriate physical address (and flags, if applicable)
;     mov eax, 0x1000
;     mov cr3, eax
    
;     ; Enable paging (and protected mode, if it isn't already active)
;     mov ebx, cr0
;     or ebx, (1 << 31) | (1 << 0)
;     mov cr0, ebx
    
;     ; Now reload the segment registers (CS, DS, SS, etc.) with the appropriate segment selectors...
    
;     mov ax, (2 * 8) | (1 << 2)
;     mov ds, ax
;     mov es, ax
;     mov fs, ax
;     mov gs, ax
    
;     jmp StartPaging

[bits 64]
[extern _start]
Start64Bit:
    ; call _setup_PML4

    call _start
    jmp $

    