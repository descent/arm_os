#include "syscall.h"

void test_syscall_args(int index,int *array){
	printk("this following message is from kernel printed by test_syscall_args\n");
	int i;
	for(i=0;i<index;i++){
		printk("the %d arg is %x\n",i,array[i]);
	}
}

syscall_fn __syscall_test(int index,int *array){
	test_syscall_args(index,array);
	return 0;
}


syscall_fn syscall_table[__NR_SYS_CALL]={
	(syscall_fn)__syscall_test,
};

int sys_call_schedule(unsigned int index,int num,int *args){
	if(syscall_table[index]){
		return (syscall_table[index])(num,args);
	}
	return -1;
}
