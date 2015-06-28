#include <kern/e1000.h>

// LAB 6: Your driver code here
#include <inc/stdio.h>
#include <inc/memlayout.h>
#include <kern/pmap.h>

volatile uint8_t *e1000bar0;

int e1000_attach (struct pci_func *pcif)
{
	pci_func_enable(pcif);
	e1000bar0 = (uint8_t *) pcif->reg_base[0];
	boot_map_region(kern_pgdir, KSTACKTOP, pcif->reg_size[0],
			pcif->reg_base[0], PTE_PCD|PTE_PWT);
	e1000bar0 = (uint8_t *) KSTACKTOP;
	cprintf("STATUS 0x%x\n", *((uint32_t *)(e1000bar0 + 8)));
	return 0;
}
