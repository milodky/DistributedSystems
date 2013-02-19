#include "MessageReceiver.h"

MessageReceiver::MessageReceiver(Inbox* in) : inbox(in)
{
	serializer = new Serializer();
}

void MessageReceiver::receive_msg(
		char* ipv4, int port, uint8_t* msg, size_t msg_len)
{
	try
	{
		double rate = (double) rand()/RAND_MAX;
		if(rate < _DROP_RATE)
		{
			fprintf(stderr, "MessageSender: Dropping packet.\n");
			return;
		}
		printf("MessageReceiver:: Received msg from %s : %d\n", ipv4, port);
		LSP_Packet packet = serializer->unmarshal(msg, msg_len);

		/* Required for conn request msgs where we dont yet have conn_id */
		packet.setHostNameAndPort(ipv4, port);
		fprintf(stderr, "Printing packet before adding to inbox\n");
		packet.print();
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


MessageReceiver::~MessageReceiver()
{
	if(serializer) delete serializer;
}
