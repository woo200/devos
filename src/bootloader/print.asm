PrintString:
  push ax
  push bx

  mov ah, 0x0e
  .Loop:
    cmp [bx], byte 0 ; Is current char NULL
    je .Exit         ; Exit when we reach end of string
    mov al, [bx]     ; Set char to print 
    int 0x10         ; BIOS interrupt for printing char
    inc bx           ; Increase STR pointer
  jmp .Loop 
  .Exit:

  pop ax
  pop bx
  ret