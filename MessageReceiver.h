#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H

#include "header.h"
#include "serializer.h"
#include "connection.h"
#include "inbox.h"

class MessageReceiver : public Uncopyable
{
private:
	Serializer* serializer;
	Inbox* inbox;

public:
	MessageReceiver(Inbox* in) : inbox(in)
	{
		serializer = new Serializer();
	}

	void receive_msg(char* ipv4, int port, uint8_t* msg, size_t msg_len)
	{
		// LSP_Packet packet = serializer.unmarshal();
		// inbox.add_msg(packet);
	}

	~MessageReceiver()
	{
		if(serializer)
			delete serializer;
	}
};

#endif
