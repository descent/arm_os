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
	nop
__vector_fiq:
	nop

