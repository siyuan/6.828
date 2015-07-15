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
	int32_t req = ipc_recv(NULL, (void *)0x20000000, NULL);
	struct jif_pkt *pkt = (struct jif_pkt *)0x20000000;
	int ret;

	if (req == NSREQ_OUTPUT) {
		ret = sys_trans_pack(pkt->jp_data, pkt->jp_len);
	}
}
