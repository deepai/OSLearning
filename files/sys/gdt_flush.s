; This will set up our new segment registers. We need to do
; something special in order to set CS. We do what is called a
; far jump. A jump that includes a segment as well as an offset.
; This is declared in C as 'extern void gdt_flush();'

global gdt_flush     ; Allows the C code to link to this
extern gp            ; Says that '_gp' is in another file
gdt_flush:
	lgdt [gp]
	mov ax, 0x10      ; 0x10 is the offset in the GDT to our data segment
	mov ds, ax
	mov es, ax
	mov ss, ax

	jmp 0x08:flush_cs   ; specify cs when jumping to flush_cs

flush_cs:
	ret