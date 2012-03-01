/*
helloworld.s:
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

.arch armv4
.global helloworld

.equ REG_FIFO,	0x50000020

.text
.align 2

helloworld:
	ldr r1,=REG_FIFO
	adr	r0,.L0
.L2:
	ldrb r2,[r0],#0x1
	str r2,[r1]
	cmp	 r2,#0x0
	bne	.L2
.L1:
	b	.L1

.align 2
.L0:	
	.ascii	"helloworld\n\0"
