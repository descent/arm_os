/*
mmu.c:
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

#ifdef TEST_MMU
#include <stdio.h>
#endif

#define PTE_BITS_L1_SECTION				(0x2)
#define PTE_L1_SECTION_PADDR_BASE_MASK	(0xfff00000)
#define PAGE_TABLE_L1_BASE_ADDR_MASK	(0xffffc000)
#define VIRT_TO_PTE_L1_INDEX(addr)	(((addr) & 0xfff00000) >> 18)

#define PTE_L1_SECTION_NO_CACHE_AND_WB	(0x0<<2)
#define PTE_L1_SECTION_DOMAIN_DEFAULT	(0x0<<5)
#define PTE_ALL_AP_L1_SECTION_DEFAULT	(0x1<<10)

#define L1_PTR_BASE_ADDR			0x30700000
#define PHYSICAL_MEM_ADDR			0x00000000
#define VIRTUAL_MEM_ADDR			0x00000000
#define MEM_MAP_SIZE				0x40000000
#define PHYSICAL_IO_ADDR			0x3F000000
#define VIRTUAL_IO_ADDR				0xc8000000
#define IO_MAP_SIZE				0x18000000

#ifndef TEST_MMU
// ===================================================================        
//  Setup domain control register - Enable all domains to client mode
// ===================================================================
/*
        MRC     p15, 0, r0, c3, c0, 0      ; Read Domain Access Control Register
        LDR     r0, =0x55555555            ; Initialize every domain entry to b01 (client)
        MCR     p15, 0, r0, c3, c0, 0      ; Write Domain Access Control Register  
*/

void set_dm()
{
  __asm__
  (
    "MRC     p15, 0, r0, c3, c0, 0\n"      // Read Domain Access Control Register
    "mov     r0, #0xffffffff\n"            // Initialize every domain entry to b11 (managers)
    "MCR     p15, 0, r0, c3, c0, 0\n"      // Write Domain Access Control Register  
  );
}

void start_mmu(void)
{
  unsigned int ttb = L1_PTR_BASE_ADDR;

  set_dm();
  asm 
  (
    "mcr p15,0,%0,c2,c0,0\n"    /* set base address of page table*/

    "mov r0,#0x1\n"
    "mcr p15,0,r0,c1,c0,0\n"    /* set back to control register, enable MMU */
    "mov r0,r0\n"
    "mov r0,r0\n"
    "mov r0,r0\n"
    :
    : "r" (ttb)
    :"r0"
  );
}
#endif

unsigned int gen_l1_pte(unsigned int paddr)
{
  return (paddr & 0xfff00000);
}

unsigned int gen_l1_pte_addr(unsigned int baddr, unsigned int vaddr)
{
  return (baddr & 0xffffc000) | VIRT_TO_PTE_L1_INDEX(vaddr);
}


// from : ds-5/examples/DS-5Examples/startup_Cortex-A7/startup.s
// ===================================================================
//  PAGE TABLE generation 
// 
//  Generate the page tables
//  Build a flat translation table for the whole address space.
//  ie: Create 4096 1MB sections from 0x000xxxxx to 0xFFFxxxxx
// 
// 
//  31                 20 19  18  17  16 15  14   12 11 10  9  8     5   4    3 2   1 0
//  |section base address| 0  0  |nG| S |AP2|  TEX  |  AP | P | Domain | XN | C B | 1 0|
// 
//  Bits[31:20]   - Top 12 bits of VA is pointer into table
//  nG[17]=0      - Non global, enables matching against ASID in the TLB when set.
//  S[16]=0       - Indicates normal memory is shared when set.
//  AP2[15]=0  
//  AP[11:10]=11  - Configure for full read/write access in all modes
//  TEX[14:12]=000
//  CB[3:2]= 00   - Set attributes to Strongly-ordered memory.
//                  (except for the code segment descriptor, see below)
//  IMPP[9]=0     - Ignored
//  Domain[5:8]=1111   - Set all pages to use domain 15
//  XN[4]=1       - Execute never on Strongly-ordered memory
//  Bits[1:0]=10  - Indicate entry is a 1MB section
// ===================================================================
void init_sys_mmu(void)
{
	unsigned int pte;
	unsigned int pte_addr;
	int j;

	for(j=0 ; j < MEM_MAP_SIZE >> 20 ; j++)
        {
		pte = gen_l1_pte(PHYSICAL_MEM_ADDR+(j<<20));
		pte |= 2; //  Bits[1:0]=10
		pte |= 0x3 << 10; // AP[11:10]=11
		pte |= 0xf << 5 ; // Domain[5:8]=1111

		pte_addr = gen_l1_pte_addr(L1_PTR_BASE_ADDR, VIRTUAL_MEM_ADDR+(j<<20));
#ifdef TEST_MMU
                printf("%4d ## pte_addr: %08x, pte: %08x\n", j, pte_addr, pte);
#else
		*(volatile unsigned int *)pte_addr=pte;
#endif
	}

	for(j=0 ; j < IO_MAP_SIZE >> 20 ; j++)
        {
		pte=gen_l1_pte(PHYSICAL_IO_ADDR+(j<<20));
		pte |= 2; //  Bits[1:0]=10
		pte |= 0x3 << 10; // AP[11:10]=11
		pte |= 0xf << 5 ; // Domain[5:8]=1111
		pte_addr = gen_l1_pte_addr(L1_PTR_BASE_ADDR, VIRTUAL_IO_ADDR+(j<<20));
#ifdef TEST_MMU
                printf("%4d (IO) ## pte_addr: %08x, pte: %08x\n", j, pte_addr, pte);
#else
		*(volatile unsigned int *)pte_addr=pte;
#endif
	}
}

#ifdef TEST_MMU
int main(int argc, char *argv[])
{

  printf("L1_PTR_BASE_ADDR: %x\n", L1_PTR_BASE_ADDR);
  init_sys_mmu();
  
  return 0;
}
#endif
