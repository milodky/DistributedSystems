#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H

#include "header.h"
#include "lsppacket.h"
#include "inbox.h"

class MessageProcessor : public Uncopyable
{
private:
	Inbox* inbox;

public:
	MessageProcessor(Inbox* in);
	int poll_inbox();
	void process_incoming_msg(LSP_Packet packet);
	~MessageProcessor();
};

#endif
