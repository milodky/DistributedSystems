#ifndef INBOX_H
#define INBOX_H

#include "header.h"
#include "serializer.h"
#include "connectionInfo.h"

class Inbox : public Uncopyable
{
private:
	queue<LSP_Packet> inbox;

public:

	void add_msg(LSP_Packet packet)
	{
		inbox.push(packet);
	}

	LSP_Packet pop_msg()
	{
		LSP_Packet packet = inbox.front();
		inbox.pop();
		return packet;
	}
};

#endif
