#include "RequestMessageProcessor.h"

RequestMessageProcessor::RequestMessageProcessor(Inbox* in, vector<ConnInfo*> *infos, pthread_mutex_t& mutex_connInfos)
	: MessageProcessor(in,infos, mutex_connInfos)
{

}

int RequestMessageProcessor::process_incoming_msg(LSP_Packet& packet)
{
	/* Call the base class function before processing further */
	if(MessageProcessor::process_incoming_msg(packet) == FAILURE)
		return FAILURE;
	switch(packet.getType())
	{
	case ACK:
		process_ack_packet(packet);
		break;
	case DATA:
		return process_data_packet(packet);
	default:
		fprintf( stderr, "Unknown Packet Type!\n");
		packet.print();
	}
	return SUCCESS;
}

int RequestMessageProcessor::process_ack_packet(LSP_Packet& packet)
{
	
	ConnInfo* connInfo = get_conn_info();

	/* Set the connection ID  on receiving first message from Server */
	if(	connInfo->getConnectionId() == 0 && connInfo->getSeqNo() == 0)
	{
		connInfo->setConnectionId(packet.getConnId());
	}

	if(MessageProcessor::process_ack_packet(packet) == FAILURE)
		return FAILURE;

	/*  If seq number is 0, send crack request to server.
    	Payload will be 'c hash len' */
	if(!testing)
	{
		if(connInfo->getSeqNo() == 0)
		{
			connInfo->incrementSeqNo();
			LSP_Packet c_pkt = create_crack_req_packet();
			fprintf( stderr, "RequestMessageProcessor::Pushing crack Request[%s] to outbox\n",
					c_pkt.getBytes());
			connInfo->add_to_outMsgs(c_pkt);
		}
	}

	return SUCCESS;
}


LSP_Packet RequestMessageProcessor::create_crack_req_packet()
{
	/**
 	* Create a crack request Data Packet:
 	* c hash lower upper
 	*/
	ConnInfo* connInfo = get_conn_info();

	uint8_t data[100];
	string startStr;
	startStr.insert(0,password_length,'a');
	string endStr;
	endStr.insert(0,password_length,'z');
	sprintf((char*) data, "c %s %s %s", hashMsg, startStr.c_str(), endStr.c_str());
	unsigned data_length = strlen((char*)data)+1;

	LSP_Packet c_pkt(
			connInfo->getConnectionId(),
			connInfo->getSeqNo(),
			data_length,
			data);

	return c_pkt;
}

int RequestMessageProcessor::process_data_packet(LSP_Packet& packet)
{
	LSP_Packet ack_packet = create_ack_packet(packet);
	switch(packet.getDataType())
	{
		case FOUND:
		{
			/* Print message Found: pass and mark COMPLETE */
			get_conn_info()->add_to_outMsgs(ack_packet);
			char* bytes = (char*)packet.getBytes();
			char pass[5], p[20];
			sscanf(bytes,"%s %s",p,pass);
			fprintf( stderr, "Found: %s\n",pass);
			return COMPLETE;
		}
		case NOTFOUND:
		{
			/* Print NOT FOUND and mark COMPLETE */
			get_conn_info()->add_to_outMsgs(ack_packet);
			fprintf( stderr, "Not Found\n");
			return COMPLETE;
		}
		default:
		{
			fprintf( stderr, "Unknown Data Type!\n");
			packet.print();
		}
	}
}

void RequestMessageProcessor::set_password_data(const char* const hashMsg, const unsigned len)
{
	this->hashMsg = hashMsg;
	this->password_length = len;
}

RequestMessageProcessor::~RequestMessageProcessor()
{

}
