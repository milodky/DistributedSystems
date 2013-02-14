#include "RequestMessageProcessor.h"

RequestMessageProcessor::RequestMessageProcessor(Inbox* in, vector<ConnInfo*> *infos, pthread_mutex_t& mutex_connInfos)
	: MessageProcessor(in,infos, mutex_connInfos)
{

}

int RequestMessageProcessor::process_incoming_msg(LSP_Packet& packet)
{
	if(MessageProcessor::process_incoming_msg(packet) == FAILURE)
		return FAILURE;
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
	return SUCCESS;
}

int RequestMessageProcessor::process_ack_packet(LSP_Packet& packet)
{
	fprintf(stderr, "RequestMessageProcessor:: Processing Ack Request from %s : %d\n", packet.getHostname(), packet.getPort());
//  If seq number is 0, send crack request to server.
//  Payload will be 'c hash len'
	ConnInfo* connInfo = get_conn_info();

	/* Set the connection ID */
	if(	connInfo->getConnectionId() == 0 && connInfo->getSeqNo() == 0)
	{
		connInfo->setConnectionId(packet.getConnId());
	}

	if(MessageProcessor::process_ack_packet(packet) == FAILURE)
		return FAILURE;

	connInfo->incrementSeqNo();
	/* Special Handling: Send Crack Request to Server */
	if(	connInfo->getSeqNo() == 1)
	{
		fprintf( stderr, "RequestMessageProcessor::Pushing crack Request(%s:%u) to outbox\n",
				hashMsg, password_length);
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

	uint8_t data[100];
	sprintf((char*) data, "c %u %s", password_length, hashMsg);
	unsigned data_length = strlen((char*)data);

	LSP_Packet c_pkt(
			connInfo->getConnectionId(),
			connInfo->getSeqNo(),
			data_length,
			data);

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
	this->password_length = len;
}

RequestMessageProcessor::~RequestMessageProcessor()
{

}
