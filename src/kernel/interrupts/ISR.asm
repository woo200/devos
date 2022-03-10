global isr1
global isr_df
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
  	pop r11
  	pop r10
  	pop r9
  	pop r8
  	pop rdx
  	pop rcx
  	pop rax
  %endmacro

[extern _idt]
idtDescriptor:
    dw 4095
    dq _idt

[extern isr1_handler]
isr1:
    PUSHALL
    call isr1_handler
    POPALL
    iretq

[extern DF_handler]
isr_df:
	PUSHALL
    call DF_handler
    POPALL
    iretq

LoadIDT:
    lidt [idtDescriptor]
    sti
    ret