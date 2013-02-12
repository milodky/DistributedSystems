#include "inbox.h"

bool Inbox::isEmpty()
{
	return inbox.size() == 0;
}

void Inbox::add_msg(LSP_Packet packet)
{
	printf("Adding packet to Inbox:\n");
	packet.print();
	inbox.push(packet);
}

LSP_Packet Inbox::pop_msg()
{
	LSP_Packet packet = inbox.front();
	inbox.pop();
	return packet;
}
