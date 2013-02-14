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

	ConnInfo* connInfo = get_conn_info();

	connInfo->incrementSeqNo();
	/* Special Handling: Send Crack Request to Server */
	if(	connInfo->getSeqNo() == 1)
	{
		LSP_Packet c_pkt = create_crack_req_packet();
		connInfo->add_to_outMsgs(c_pkt);
	}

	return SUCCESS;
}

/**
 * Create a crack request Data:
 * byte[0] = 'c', byte[1] = len, following bytes = hash
 */
LSP_Packet RequestMessageProcessor::create_crack_req_packet()
{
	ConnInfo* connInfo = get_conn_info();

	unsigned data_length = 2 + hashMsglen; /* 1 byte for c and 1 for size */

	uint8_t* data = new uint8_t[data_length];
	data[0] = 'c';
	data[1] = hashMsglen;
	memcpy(data + 2, hashMsg, hashMsglen);

	LSP_Packet c_pkt(
			connInfo->getConnectionId(),
			connInfo->getSeqNo(),
			data_length,
			data);

	delete data;
	return c_pkt;
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

void RequestMessageProcessor::set_password_data(const char* const hashMsg, const unsigned len)
{
	this->hashMsg = hashMsg;
	this->hashMsglen = len;
}

RequestMessageProcessor::~RequestMessageProcessor()
{

}
