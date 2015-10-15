cortex_a_mmu:cortex_a_mmu.o
	gcc -DTEST_MMU -o $@ $<
cortex_a_mmu.o:cortex_a_mmu.c
	gcc -DTEST_MMU -c $<
mmu:mmu.o
	gcc -DTEST_MMU -o $@ $<
mmu.o:mmu.c
	gcc -DTEST_MMU -c $<
