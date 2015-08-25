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
	int r;

	while (1) {
		if ((r = sys_page_alloc(0, &nsipcbuf, PTE_P|PTE_U|PTE_W)) < 0)
			panic("sys_page_map: %e", r);
		memset(&nsipcbuf, 0, PGSIZE);
		r = sys_receive_pack(nsipcbuf.pkt.jp_data, &nsipcbuf.pkt.jp_len);
		if (r == 0) {
			ipc_send(ns_envid, NSREQ_INPUT, &nsipcbuf, PTE_P|PTE_W|PTE_U);
		}
		sys_page_unmap(0, &nsipcbuf);
		sys_yield();
	}
}
