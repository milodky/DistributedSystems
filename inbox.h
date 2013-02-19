#ifndef INBOX_H
#define INBOX_H

#include <queue>

#include "header.h"
#include "lsppacket.h"

class Inbox : public Uncopyable
{
private:
	queue<LSP_Packet> inbox;
	pthread_mutex_t mutex_inbox;

public:
	Inbox();

	bool isEmpty();
	void add_msg(LSP_Packet packet);
	LSP_Packet pop_msg();

	~Inbox();
};

#endif
