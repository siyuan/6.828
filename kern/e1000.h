#ifndef JOS_KERN_E1000_H
#define JOS_KERN_E1000_H

#define TX_DESC_NUM 16
#define MAX_ETH_PAC 1518
#include <kern/pci.h>

int e1000_attach (struct pci_func *pcif);
void e1000_init (struct pci_func *pcif);
#endif	// JOS_KERN_E1000_H
