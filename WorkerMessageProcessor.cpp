#include "WorkerMessageProcessor.h"
#include <sstream>
using namespace std;

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

int WorkerMessageProcessor::process_ack_packet(LSP_Packet& packet)
{
//  If seq number is 0, send join request to server.
//  Payload will be 'j'
	ConnInfo* connInfo = get_conn_info();

	/* Set the connection ID */
	if(	connInfo->getConnectionId() == 0 && connInfo->getSeqNo() == 0)
	{
		connInfo->setConnectionId(packet.getConnId());
	}
	if(!MessageProcessor::process_ack_packet(packet))
		return FAILURE;

	connInfo->incrementSeqNo();
	/* Special Handling: Send Crack Request to Server */
	if(	connInfo->getSeqNo() == 1)
	{
		LSP_Packet j_pkt = create_join_req_packet();
		connInfo->add_to_outMsgs(j_pkt);
	}

	return SUCCESS;
}

/**
 * Create a crack request Data:
 * byte[0] = 'c', byte[1] = len, following bytes = hash
 */
LSP_Packet WorkerMessageProcessor::create_join_req_packet()
{
	ConnInfo* connInfo = get_conn_info();

	unsigned data_length = 1;

	uint8_t* data = new uint8_t[data_length];
	data[0] = 'j';

	LSP_Packet c_pkt(
			connInfo->getConnectionId(),
			connInfo->getSeqNo(),
			data_length,
			data);

	delete data;
	return c_pkt;
}

void WorkerMessageProcessor::process_data_packet(LSP_Packet& packet)
{
	switch(packet.getDataType())
	{
	case CRACKREQUEST:
//		Update seq number. If outbox has any msg with sequence number less than
//		current, remove from outbox. This case will only happen when server
//		sends a crack request after the worker sends an 'Alive' message,
//		but before the server gets it.
		process_crack_request(packet);
		break;
	default:
		fprintf( stderr, "Unknown Data Type!\n");
		packet.print();
	}
}

void WorkerMessageProcessor::process_crack_request(LSP_Packet& packet)
{
//	This comes from the server and has the following format:
//	c hash lower upper
	uint8_t* bytes = packet.getBytes();
	string s((char*)bytes);
	stringstream iss(s);
	string ignore;
	iss >> ignore;
	string hash;
	iss >> hash;
	string startString;
	iss >> startString;
	int start = atoi(startString.c_str());
	string endString;
	iss >> endString;
	int end = atoi(endString.c_str());
	string lengthString;
	iss >> lengthString;
	int length = atoi(lengthString.c_str());
	char* password;
	//Start as a separate thread
	process_crack_request(hash, start, end, length, password);
}

void WorkerMessageProcessor::process_crack_request(string sha, int start, int end, int length, char* password)
{
	for(int i = start; i < end; i++)
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

WorkerMessageProcessor::~WorkerMessageProcessor()
{

}
