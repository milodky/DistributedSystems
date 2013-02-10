#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H

#include "header.h"
#include "serializer.h"
#include "inbox.h"

class MessageReceiver : public Uncopyable
{
private:
	Serializer serializer;
	Inbox inbox;

public:

	void receive_msg(char* ipv4, int port, uint8_t* msg, size_t msg_len)
	{
		LSP_Packet packet = serializer.unmarshal();
		inbox.add_msg(packet);
	}
};

#endif
