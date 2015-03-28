/* See COPYRIGHT for copyright information. */

#include <inc/mmu.h>
#include <inc/memlayout.h>
#include <inc/trap.h>



###################################################################
# exceptions/interrupts
###################################################################

/* TRAPHANDLER defines a globally-visible function for handling a trap.
 * It pushes a trap number onto the stack, then jumps to _alltraps.
 * Use TRAPHANDLER for traps where the CPU automatically pushes an error code.
 *
 * You shouldn't call a TRAPHANDLER function from C, but you may
 * need to _declare_ one in C (for instance, to get a function pointer
 * during IDT setup).  You can declare the function with
 *   void NAME();
 * where NAME is the argument passed to TRAPHANDLER.
 */
#define TRAPHANDLER(name, num)						\
	.globl name;		/* define global symbol for 'name' */	\
	.type name, @function;	/* symbol type is function */		\
	.align 2;		/* align function definition */		\
	name:			/* function starts here */		\
	pushl $(num);							\
	jmp _alltraps

/* Use TRAPHANDLER_NOEC for traps where the CPU doesn't push an error code.
 * It pushes a 0 in place of the error code, so the trap frame has the same
 * format in either case.
 */
#define TRAPHANDLER_NOEC(name, num)					\
	.globl name;							\
	.type name, @function;						\
	.align 2;							\
	name:								\
	pushl $0;							\
	pushl $(num);							\
	jmp _alltraps

.text

/*
 * Lab 3: Your code here for generating entry points for the different traps.
 */
TRAPHANDLER_NOEC(hdl0, 0);
TRAPHANDLER_NOEC(hdl1, 1);
TRAPHANDLER_NOEC(hdl2, 2);
TRAPHANDLER_NOEC(hdl3, 3);
TRAPHANDLER_NOEC(hdl4, 4);
TRAPHANDLER_NOEC(hdl5, 5);
TRAPHANDLER_NOEC(hdl6, 6);
TRAPHANDLER_NOEC(hdl7, 7);
TRAPHANDLER(hdl8, 8);
TRAPHANDLER(hdl10, 10);
TRAPHANDLER(hdl11, 11);
TRAPHANDLER(hdl12, 12);
TRAPHANDLER(hdl13, 13);
TRAPHANDLER(hdl14, 14);
TRAPHANDLER_NOEC(hdl16, 16);
TRAPHANDLER(hdl17, 17);
TRAPHANDLER_NOEC(hdl18, 18);
TRAPHANDLER_NOEC(hdl19, 19);

/*
 * Lab 3: Your code here for _alltraps
 */
_alltraps:
	pushw $0;
	pushw %ds;
	pushw $0;
	pushw %es;
	pushal;

	movw $GD_KD, %ax;
	movw %ax, %ds;
	movw %ax, %es;

	pushl %esp;
	call trap;
