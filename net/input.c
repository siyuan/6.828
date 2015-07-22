#include "ns.h"

extern union Nsipc nsipcbuf;

void
input(envid_t ns_envid)
{
	binaryname = "ns_input";

	// LAB 6: Your code here:
	// 	- read a packet from the device driver
	//	- send it to the network server
	// Hint: When you IPC a page to the network server, it will be
	// reading from it for a while, so don't immediately receive
	// another packet in to the same physical page.
	int32_t req;
	int r;
	struct jif_pkt *pkt;
	pkt = (struct jif_pkt *)REQVA;

	if ((r = sys_page_alloc(0, pkt, PTE_P|PTE_U|PTE_W)) < 0)
		panic("sys_page_map: %e", r);
	while (1) {
		r = sys_receive_pack(pkt->jp_data, &(pkt->jp_len));
		if (r == 0) {
			ipc_send(ns_envid, NSREQ_INPUT, pkt, PTE_P|PTE_W|PTE_U);
			break;
		}
	}
	sys_page_unmap(0, pkt);
}
