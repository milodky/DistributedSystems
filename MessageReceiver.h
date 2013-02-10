#ifndef MESSAGERECEIVER_H
#define MESSAGERECEIVER_H

#include "header.h"
#include "serializer.h"

class MessageReceiver : public Uncopyable
{
private:
	Serializer serializer;
	queue<LSP_Packet*> inbox;

public:

	void receiver_msg(char* ipv4, int port, uint8_t* msg, size_t msg_len)
	{
		LSP_Packet packet = serializer.unmarshal()
	}


};

#endif
