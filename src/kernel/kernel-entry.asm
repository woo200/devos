jmp EnterProtectedMode

%include "src/kernel/gdt.asm"

EnterProtectedMode:
    call EnableA20        ; Enable A20 Line
    cli
    lgdt [gdt_descriptor] ; Load GDT

    jmp EnablePaging

EnableA20:
    in al, 0x92
    or al, 2
    out 0x92, al
    ret

EnablePaging:
    ; Enable PAE
    mov edx, cr4
    or  edx, (1 << 5)
    mov cr4, edx
    
    ; Set LME (long mode enable)
    mov ecx, 0xC0000080
    rdmsr
    or  eax, (1 << 8)
    wrmsr
    
    ; Replace 'pml4_table' with the appropriate physical address (and flags, if applicable)
    mov eax, pml4_table
    mov cr3, eax
    
    ; Enable paging (and protected mode, if it isn't already active)
    or ebx, (1 << 31) | (1 << 0)
    mov cr0, ebx
    
    ; Now reload the segment registers (CS, DS, SS, etc.) with the appropriate segment selectors...
    
    mov ax, DATA_SEL
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    jmp codeseg:StartLongMode

[bits 64]
StartLongMode:
    jmp $
    