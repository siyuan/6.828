#include "ns.h"
#include <kern/e1000.h>

extern union Nsipc nsipcbuf;

void
output(envid_t ns_envid)
{
	binaryname = "ns_output";

	// LAB 6: Your code here:
	// 	- read a packet from the network server
	//	- send the packet to the device driver
	int r;
	int32_t req;
	struct jif_pkt *pkt;

	while (1){
		envid_t whom;
		if ((r = sys_page_alloc(0, &nsipcbuf, PTE_P|PTE_U|PTE_W)) < 0)
			panic("sys_page_map: %e", r);
		memset(&nsipcbuf, 0, PGSIZE);
		req = ipc_recv((int32_t *)&whom, &nsipcbuf, NULL);
		if ( whom != ns_envid) {
			cprintf("output who != ns_envid\n");
			return;
		}
		pkt = &nsipcbuf.pkt;
		if (req == NSREQ_OUTPUT) {
			cprintf("output: pkt->jp_len 0x%x\n",pkt->jp_len);
			r = sys_trans_pack(pkt->jp_data, pkt->jp_len);
			if (r == 0) {
			}
		}
		sys_page_unmap(0, &nsipcbuf);
		sys_yield();
	}
}
