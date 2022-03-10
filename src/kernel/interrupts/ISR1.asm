global isr1
global LoadIDT

%macro PUSHALL 0
    push rax
    push rcx
    push rdx
    push r8
    push r9
    push r10
    push r11
%endmacro

%macro POPALL 0
    push r11
    push r10
    push r9
    push r8
    push rdx
    push rcx
    push rax
%endmacro

[extern _idt]
idtDescriptor:
    dw 4095
    dq _idt

[extern isr1_handler]
isr1:
    PUSHALL
    cld
    call isr1_handler
    POPALL
    iretq

LoadIDT:
    lidt [idtDescriptor]
    sti
    ret