#include <kern/e1000.h>

// LAB 6: Your driver code here
#include <inc/stdio.h>
#include <inc/memlayout.h>
#include <kern/pmap.h>
#include <kern/e1000_hw.h>

volatile uint8_t *e1000bar0;

int e1000_attach (struct pci_func *pcif)
{
	pci_func_enable(pcif);
	e1000bar0 = (uint8_t *) pcif->reg_base[0];
	boot_map_region(kern_pgdir, KSTACKTOP, pcif->reg_size[0],
			pcif->reg_base[0], PTE_PCD | PTE_PWT | PTE_W);
	e1000bar0 = (uint8_t *) KSTACKTOP;
	cprintf("STATUS 0x%x\n", *((uint32_t *)(e1000bar0 + 8)));
	e1000_init(pcif);
	return 0;
}

void e1000_init (struct pci_func *pcif)
{
	struct Page *pp, *pptmp;
	physaddr_t patmp;
	int i;
	struct e1000_tx_desc *desc;

	pp = page_alloc(ALLOC_ZERO);
	pp->pp_ref++;
	desc = page2kva(pp);

	for (i=0; i<TX_DESC_NUM/2; i++) {
		pptmp = page_alloc(ALLOC_ZERO);
		pptmp->pp_ref++;
		patmp = page2pa(pptmp);
		(desc + 2 * i)->buffer_addr = patmp;
		(desc + 2 * i + 1)->buffer_addr = patmp + MAX_ETH_PAC;
	}

	*((uint32_t *)(e1000bar0 + E1000_TDBAL)) = page2pa(pp);
	*((uint32_t *)(e1000bar0 + E1000_TDBAH)) = 0;
	*((uint32_t *)(e1000bar0 + E1000_TDLEN)) = TX_DESC_NUM * sizeof(struct e1000_tx_desc);
	*((uint32_t *)(e1000bar0 + E1000_TDH)) = 0;
	*((uint32_t *)(e1000bar0 + E1000_TDT)) = 0;
	*(e1000bar0 + E1000_TCTL) |= E1000_TCTL_EN;
	*(e1000bar0 + E1000_TCTL) |= E1000_TCTL_PSP;
	*(e1000bar0 + E1000_TCTL) |= (0x10 << 4);
	*(e1000bar0 + E1000_TCTL) |= (0x40 << 12);
	*((uint32_t *)(e1000bar0 + E1000_TIPG)) = 10;
}
