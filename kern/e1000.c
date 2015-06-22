#include <kern/e1000.h>

// LAB 6: Your driver code here
#include <inc/stdio.h>
int e1000_attach (struct pci_func *pcif)
{
	cprintf("e1000_attach begin\n");
	pci_func_enable(pcif);
	return 0;
}
