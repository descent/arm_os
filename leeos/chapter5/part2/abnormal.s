/*
abnormal.s:
Copyright (C) 2009  david leels <davidontech@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.
*/

.equ DISABLE_IRQ,0x80
.equ DISABLE_FIQ,0x40
.equ SYS_MOD,0x1f
.equ IRQ_MOD,0x12
.equ FIQ_MOD,0x11
.equ SVC_MOD,0x13
.equ ABT_MOD,0x17
.equ UND_MOD,0x1b
.equ MOD_MASK,0x1f


.macro CHANGE_TO_SVC
        msr     cpsr_c,#(DISABLE_FIQ|DISABLE_IRQ|SVC_MOD)
.endm

.macro CHANGE_TO_IRQ
        msr     cpsr_c,#(DISABLE_FIQ|DISABLE_IRQ|IRQ_MOD)
.endm



.global	__vector_undefined
.global	__vector_swi
.global	__vector_prefetch_abort
.global	__vector_data_abort
.global	__vector_reserved
.global	__vector_irq
.global	__vector_fiq

.text
.code 32

__vector_undefined:
	nop
__vector_swi:
	nop
__vector_prefetch_abort:	
	nop
__vector_data_abort:
	nop
__vector_reserved:
	nop
__vector_irq:
	sub r14,r14,#4
	stmfd r13!,{r14}
	mrs r14,spsr
	stmfd r13!,{r14}
	CHANGE_TO_SVC
	stmfd r13!,{r0-r3}
	bl common_irq_handler
	ldmfd r13!,{r0-r3}
	CHANGE_TO_IRQ
	ldmfd r13!,{r14}
	msr spsr,r14
	ldmfd r13!,{pc}^


__vector_fiq:
	nop

