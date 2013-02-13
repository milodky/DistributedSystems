#include "RequestMessageProcessor.h"

RequestMessageProcessor::RequestMessageProcessor(Inbox* in, vector<ConnInfo*> *infos)
	: MessageProcessor(in,infos)
{

}

void RequestMessageProcessor::process_incoming_msg(LSP_Packet& packet)
{
	MessageProcessor::process_incoming_msg(packet);
	switch(packet.getType())
	{
	case ACK:
		process_ack_packet(packet);
		break;
	case DATA:
		process_data_packet(packet);
		break;
	default:
		fprintf( stderr, "Unknown Packet Type!\n");
		packet.print();
	}
}

int RequestMessageProcessor::process_ack_packet(LSP_Packet& packet)
{
//  If seq number is 0, send crack request to server.
//  Payload will be 'c hash len'
	if(!MessageProcessor::process_ack_packet(packet))
		return FAILURE;


	return SUCCESS;
}

void RequestMessageProcessor::process_data_packet(LSP_Packet& packet)
{
	LSP_Packet ack_packet = create_ack_packet(packet);
	switch(packet.getDataType())
	{
	case FOUND:
	{
//		Send ack
		get_conn_info()->add_to_outMsgs(ack_packet);
//		return the password that is found. For now being printed here.
		fprintf( stderr, "Found: ");
//		XXX - remove f from beginning of bytes.
		printBytes(packet.getBytes(), packet.getLen());
		break;
	}
	case NOTFOUND:
	{
//		Send ack
		get_conn_info()->add_to_outMsgs(ack_packet);
//		return password not found. For now being printed here. (could return -1 as a string perhaps)
		fprintf( stderr, "Not Found\n");
		break;
	}
	default:
	{
		fprintf( stderr, "Unknown Data Type!\n");
		packet.print();
	}
	}

//write code
//remove msg from outbox, when seqno exceeds that of last message, and packet type not ack.
}

RequestMessageProcessor::~RequestMessageProcessor()
{

}
