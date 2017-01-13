

.global _read_cr0
  _read_cr0:
        movl %cr0, %eax
        ret

.global _write_cr0
  _write_cr0:
        pushl %ebp
        movl %esp,%ebp
        movl 8(%ebp),%eax
        movl %cr0, %eax
        popl %ebp
        ret

.global _read_cr3
  _read_cr3:
        movl %cr3, %eax
        ret

.global _write_cr3
  _write_cr3:
        pushl %ebp
        movl %esp,%ebp
        movl 8(%ebp),%eax
        movl %cr3, %eax
        popl %ebp
        ret
