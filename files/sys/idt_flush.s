; Loads the IDT defined in '_idtp' into the processor.
; This is declared in C as 'extern void idt_load();'
global idt_load
extern idtp
idt_load:
	lidt [idtp]
	ret

%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	cli
	push	dword 0                     ; push 0 as error code
	push	dword %1                    ; push the interrupt number
	jmp     common_interrupt_handler    ; jump to the common handler
	sti
	ret
%endmacro

%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	cli
	push	dword %1                    ; push the interrupt number
	jmp	common_interrupt_handler    ; jump to the common handler
	sti
	ret
%endmacro

%macro no_error_code_irq_handler 2
global irq_handler_%1
irq_handler_%1:
	cli
	push	dword 0                     ; push 0 as error code
	push	dword %2                    ; push the interrupt number
	jmp     common_irq_handler    ; jump to the common handler
	sti
	ret
%endmacro

extern fault_handler
extern irq_handler

common_interrupt_handler:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp   ; Push us the stack
	push eax
	mov eax, fault_handler
	call eax       ; A special call, preserves the 'eip' register
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8     ; Cleans up the pushed error code and pushed ISR number
	iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!

; This is a stub that we have created for IRQ based ISRs. This calls
; '_irq_handler' in our C code. We need to create this in an 'irq.c'
common_irq_handler:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp
    push eax
    mov eax, irq_handler
    call eax
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8
    iret

no_error_code_interrupt_handler 0       ; create handler for interrupt 0
no_error_code_interrupt_handler 1       ; create handler for interrupt 1
no_error_code_interrupt_handler 2       ; create handler for interrupt 2
no_error_code_interrupt_handler 3       ; create handler for interrupt 3
no_error_code_interrupt_handler 4       ; create handler for interrupt 4
no_error_code_interrupt_handler 5       ; create handler for interrupt 5
no_error_code_interrupt_handler 6       ; create handler for interrupt 6
no_error_code_interrupt_handler 7       ; create handler for interrupt 7
error_code_interrupt_handler 8			; create handler for interrupt 8
no_error_code_interrupt_handler 9       ; create handler for interrupt 9
error_code_interrupt_handler 10			; create handler for interrupt 10
error_code_interrupt_handler 11			; create handler for interrupt 11
error_code_interrupt_handler 12			; create handler for interrupt 12
error_code_interrupt_handler 13			; create handler for interrupt 13
error_code_interrupt_handler 14			; create handler for interrupt 14
no_error_code_interrupt_handler 15       ; create handler for interrupt 15
no_error_code_interrupt_handler 16      ; create handler for interrupt 16
no_error_code_interrupt_handler 17       ; create handler for interrupt 17
no_error_code_interrupt_handler 18       ; create handler for interrupt 18
no_error_code_interrupt_handler 19       ; create handler for interrupt 19
no_error_code_interrupt_handler 20       ; create handler for interrupt 20
no_error_code_interrupt_handler 21       ; create handler for interrupt 21
no_error_code_interrupt_handler 22       ; create handler for interrupt 22
no_error_code_interrupt_handler 23       ; create handler for interrupt 23
no_error_code_interrupt_handler 24       ; create handler for interrupt 24
no_error_code_interrupt_handler 25       ; create handler for interrupt 25
no_error_code_interrupt_handler 26       ; create handler for interrupt 26
no_error_code_interrupt_handler 27       ; create handler for interrupt 27
no_error_code_interrupt_handler 28       ; create handler for interrupt 28
no_error_code_interrupt_handler 29       ; create handler for interrupt 29
no_error_code_interrupt_handler 30       ; create handler for interrupt 30
no_error_code_interrupt_handler 31       ; create handler for interrupt 31

no_error_code_irq_handler 0,32
no_error_code_irq_handler 1,33
no_error_code_irq_handler 2,34
no_error_code_irq_handler 3,35
no_error_code_irq_handler 4,36
no_error_code_irq_handler 5,37
no_error_code_irq_handler 6,38
no_error_code_irq_handler 7,39
no_error_code_irq_handler 8,40
no_error_code_irq_handler 9,41
no_error_code_irq_handler 10,42
no_error_code_irq_handler 11,43
no_error_code_irq_handler 12,44
no_error_code_irq_handler 13,45
no_error_code_irq_handler 14,46
no_error_code_irq_handler 15,47



