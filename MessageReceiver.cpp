#include "MessageReceiver.h"

void MessageReceiver::receive_msg(
		char* ipv4, int port, uint8_t* msg, size_t msg_len)
{
	try
	{
		LSP_Packet packet = serializer->unmarshal(msg, msg_len);
		inbox->add_msg(packet);
	}
	catch (const std::exception& ex)
	{
		fprintf(stderr, "Packet Dropped from %s : %d\n", ipv4, port);
		fprintf(stderr, "%s", ex.what());
	}
	catch (...)
	{
		fprintf(stderr, "Packet Dropped from %s : %d\n", ipv4, port);
	}
}

MessageReceiver::MessageReceiver(Inbox* in) : inbox(in)
{
	serializer = new Serializer();
}

MessageReceiver::~MessageReceiver()
{
	if(serializer) delete serializer;
	if(inbox) delete inbox;
}
