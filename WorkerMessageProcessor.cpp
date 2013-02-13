#include "WorkerMessageProcessor.h"

WorkerMessageProcessor::WorkerMessageProcessor(Inbox* in, vector<ConnInfo*> *infos)
	: MessageProcessor(in,infos)
{

}

void WorkerMessageProcessor::process_incoming_msg(LSP_Packet& packet)
{
	MessageProcessor::process_incoming_msg(packet);
	switch(packet.getType())
	{
	case ACK:
		break;
	case DATA:
	{
		process_data_packet(packet);
		break;
	}
	default:
		fprintf( stderr, "Unknown Packet Type!\n");
		packet.print();
	}
}

void WorkerMessageProcessor::process_data_packet(LSP_Packet& packet)
{
	switch(packet.getDataType())
	{
	case CRACKREQUEST:
		break;
	default:
		fprintf( stderr, "Unknown Data Type!\n");
		packet.print();
	}

//write code
//remove msg from outbox, when seqno exceeds that of last message, and packet type not ack.
}

WorkerMessageProcessor::~WorkerMessageProcessor()
{

}
