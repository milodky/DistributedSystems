#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H

#include "header.h"
#include "lsppacket.h"
#include "serializer.h"
#include "connection.h"
#include "inbox.h"

class MessageReceiver : public Uncopyable
{
private:
	Serializer* serializer;
	Inbox* inbox;

public:
	MessageReceiver(Inbox* in);

	void receive_msg(char* ipv4, int port, uint8_t* msg, size_t msg_len);

	~MessageReceiver();
};

#endif
