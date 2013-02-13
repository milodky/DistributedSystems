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

void WorkerMessageProcessor::process_ack_packet(LSP_Packet& packet)
{
//  If seq number is 0, send join request to server.
//  Payload will be 'j'
	MessageProcessor::process_ack_packet(packet);
}

void WorkerMessageProcessor::process_data_packet(LSP_Packet& packet)
{
	switch(packet.getDataType())
	{
	case CRACKREQUEST:
//		Update seq number. If outbox has any msg with sequence number less than current, remove from outbox. This case will only happen when server
//		sends a crack request after the worker sends an 'Alive' message, but before the server gets it.

		break;
	default:
		fprintf( stderr, "Unknown Data Type!\n");
		packet.print();
	}

//write code
//remove msg from outbox, when seqno exceeds that of last message, and packet type not ack.
}

void WorkerMessageProcessor::process_crack_request(LSP_Packet& packet)
{
	uint8_t* bytes = packet.getBytes();
}

void WorkerMessageProcessor::process_crack_request(string sha, int start, int count, int length, char* password)
{
	for(int i = start; i < count; i++)
	{
		string str = numToString(i,length);
		if(str.compare(password)==0)
		{
			printf("Found: %s",str.c_str());
			break;
		}
	}
}

string WorkerMessageProcessor::numToString(int x,int length)
{
	string str = "";
	int y;
	do {
		y=x%26;
		str=char('a'+y) +str;
		x/=26;
	}while(x);
	str.insert(0,length-str.length(),'a');
	return str;
}

void WorkerMessageProcessor::process_crack_request(uint8_t* sha, uint8_t* start, uint8_t* count, uint8_t* length, char* password)
{
	//convert appropriately and call process_crack_request(string sha, int start, int count, int length, char* password)
}


WorkerMessageProcessor::~WorkerMessageProcessor()
{

}
