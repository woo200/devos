PROGRAM_SPACE equ 0x8000

ReadDisk:
  mov ah, 0x02          ; Read disk magic number
  mov bx, PROGRAM_SPACE ; Define program space start
  mov al, 64            ; Read 32kb

  mov dl, [BOOT_DISK]
  mov ch, 0x00          ; Cylinder 0
  mov dh, 0x00          ; Head 0
  mov cl, 0x02          ; Sector 2

  int 0x13              ; Read the disk into memory [bx]

  jc DiskReadFailed     ; Jump to DiskReadFailed if the disk read has failed

  ret

BOOT_DISK:
  db 0

DiskReadErrorString:
  db 'Disk Read Failed', 0

DiskReadFailed:
  mov bx, DiskReadErrorString
  call PrintString

  jmp $