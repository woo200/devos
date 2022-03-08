jmp EnterProtectedMode

; %include "src/kernel/gdt.asm"

[bits 16]
[extern _setup_GDT]
EnterProtectedMode:
    call EnableA20        ; Enable A20 Line
    
    call _setup_GDT
    cli
    lgdt [0x5000] ; Load GDT

    mov eax, cr0 
    or al, 1       ; set PE (Protection Enable) bit in CR0 (Control Register 0)
    mov cr0, eax

    jmp EnablePaging

EnableA20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

[bits 32]
EnablePaging:
    mov ebx, cr0
    and ebx, ~(1 << 31)
    mov cr0, ebx
    
    ; Enable PAE
    mov edx, cr4
    or  edx, (1 << 5)
    mov cr4, edx
    
    ; Set LME (long mode enable)
    mov ecx, 0xC0000080
    rdmsr
    or  eax, (1 << 8)
    wrmsr

    jmp StartPaging

[extern _start]
[extern _setup_PML4]
StartPaging:
    call _setup_PML4

    ; Replace 'pml4_table' with the appropriate physical address (and flags, if applicable)
    mov eax, 0x1000
    mov cr3, eax
    
    ; Enable paging (and protected mode, if it isn't already active)
    or ebx, (1 << 31) | (1 << 0)

    push 0xdeadbeef 
    push 0xdeadbeef 
    push 0xdeadbeef 
    push 0xdeadbeef 
    push 0xdeadbeef 
    push 0xdeadbeef 

    mov cr0, ebx
    
    ; Now reload the segment registers (CS, DS, SS, etc.) with the appropriate segment selectors...
    
    mov ax, (2 * 8) | (1 << 2) ; GDT entry #2
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call _start
    jmp $

    