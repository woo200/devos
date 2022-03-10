global isr1
global LoadIDT

[extern _idt]
idtDescriptor:
    dw 4095
    dq _idt

[extern isr1_handler]
isr1:
    pushad
    cld
    call isr1_handler
    popad
    iretq

LoadIDT:
    lidt [idtDescriptor]
    sti
    ret