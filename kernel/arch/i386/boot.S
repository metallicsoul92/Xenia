# Declare constants for the multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b

#This will set up our new segment registers. We need to do
# something special in order to set CS. We do what is called a
# far jump. A jump that includes a segment as well as an offset.
# This is declared in C as 'extern void gdt_flush();'
.global _gdt_flush     # Allows the C code to link to this
.global _gp            # Says that '_gp' is in another file
_gdt_flush:
    lgdt _gp        # Load the GDT with our '_gp' which is a special pointer
    mov %ax, 0x10      # 0x10 is the offset in the GDT to our data segment
    mov %ds, %eax
    mov %es, %eax
    mov %fs, %eax
    mov %gs, %eax
    mov %ss, %eax
    jmp flush2   # 0x08 is the offset to our code segment: Far jump!

flush2:
    ret               # Returns back to the C code!


.size _start, . - _start
