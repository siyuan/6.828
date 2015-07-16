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
	int32_t req = ipc_recv(NULL, (void *)REQVA, NULL);
	struct jif_pkt *pkt = (struct jif_pkt *)REQVA;
	int ret;

	cprintf("output: envid: 0x%x\n", sys_getenvid());
	cprintf("output: pkt addr 0x%x\n", pkt);
	cprintf("output: pkt->jp_len %d\n", pkt->jp_len);
	while (1){
	if (req == NSREQ_OUTPUT) {
		ret = sys_trans_pack(pkt->jp_data, pkt->jp_len);
	}
}
}
