#ifndef INBOX_H
#define INBOX_H

#include "header.h"
#include "lsppacket.h"

class Inbox : public Uncopyable
{
private:
	queue<LSP_Packet> inbox;

public:
	bool isEmpty();
	void add_msg(LSP_Packet packet);
	LSP_Packet pop_msg();
};

#endif
