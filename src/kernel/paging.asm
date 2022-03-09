PageTableEntry equ 0x1000

SetUpIdentityPaging:
	mov edi, PageTableEntry
	mov cr3, edi

	mov dword [edi], 0x2003 ; 0x1000 <-- 0x2003
	add edi, 0x1000
	mov dword [edi], 0x3003 ; 0x2000 <-- 0x3003
	add edi, 0x1000
	mov dword [edi], 0x4003 ; 0x3000 <-- 0x4003
	add edi, 0x1000

	mov ebx, 0x00000003 ; EBX <-- 0x3
	mov ecx, 512 ; LOOP 512 times

	; Start at 0x4000
	.SetEntry:
		mov dword [edi], ebx ; Move 0x3 into memory pos
		add ebx, 0x1000 ; Page Directory Entry ADDR
		add edi, 8 ; Page Directory Entry Size = 8; Add new entry 
		loop .SetEntry

	mov eax, cr4
	or eax, 1 << 5
	mov cr4, eax

	mov ecx, 0xC0000080
	rdmsr
	or eax, 1 << 8
	wrmsr

	mov eax, cr0
	or eax, 1 << 31
	mov cr0, eax

	ret