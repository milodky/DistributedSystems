#include "MessageProcessor.h"

MessageProcessor::MessageProcessor(Inbox* in, vector<ConnInfo*> *infos, pthread_mutex_t& mutex_connInfos)
	: inbox(in), mutex_connInfos(mutex_connInfos), connInfos(infos)
{

}

int MessageProcessor::poll_inbox()
{
	fprintf(stderr, "MessageProcessor:: Polling inbox.. \n");
	while(true)
	{
		/* Empty Inbox: Life is chill! :-) */
		if(inbox->isEmpty()) continue;

		LSP_Packet packet = inbox->pop_msg();
		fprintf(stderr, "MessageProcessor:: Received Packet. \n");
		packet.print();
		process_incoming_msg(packet);
	}
}

ConnInfo* MessageProcessor::get_conn_info()
{
	assert(connInfos->size()==1);
	return (*connInfos)[0];
}

ConnInfo* MessageProcessor::get_conn_info(int connId)
{
	for(vector<ConnInfo*>::iterator it=connInfos->begin();
				it!=connInfos->end(); ++it)
	{
		if((*it)->getConnectionId() == connId)
			return (*it);

	}
	assert (false);
	return NULL;
}

void MessageProcessor::stamp_msg_type(LSP_Packet& packet)
{
	if(packet.getConnId() == 0 && packet.getSeqNo() == 0 &&
			packet.getLen() == 0)
	{
		packet.setType(CONN_REQ);
	}
	else if(packet.getConnId() != 0 && packet.getLen() == 0)
	{
		packet.setType(ACK);
	}
	else if(packet.getConnId() != 0 && packet.getSeqNo() != 0 &&
			packet.getLen() != 0)
	{
		packet.setType(DATA);
	}
	else
	{
		fprintf( stderr, "MessageProcessor:: Unknown Packet Type!\n");
		packet.print();
	}
}

void MessageProcessor::stamp_data_type(LSP_Packet& packet)
{
	uint8_t* bytes = packet.getBytes();
	if(bytes[0] == 'j')
		packet.setDataType(JOINREQUEST);
	else if(bytes[0] == 'c')
		packet.setDataType(CRACKREQUEST);
	else if(bytes[0] == 'f')
		packet.setDataType(FOUND);
	else if (bytes[0] == 'x')
		packet.setDataType(NOTFOUND);
	else if (bytes[0] == 'a')
		packet.setDataType(ALIVE);
	else
		packet.setDataType(NOTKNOWN);
}

int MessageProcessor::check_msg_sequence_and_pop_outbox(LSP_Packet& packet)
{
//	ConnInfo* connInfo = get_conn_info(packet.getConnId());
//	LSP_Packet out_pkt = connInfo->get_front_msg();
//
//	assert (packet.getConnId() == out_pkt.getConnId() || out_pkt.getConnId() == 0);
//
//	/*	TODO Server gets higher priority when both send packets with the same seq no */
//	if((packet.getSeqNo() == out_pkt.getSeqNo() && packet.getType() == ACK) ||
//			(packet.getSeqNo() == out_pkt.getSeqNo() + 1 && packet.getType() == DATA))
//	{
//		/* Pop from conn info */
//		if(packet.getSeqNo() == out_pkt.getSeqNo() && packet.getType() == ACK)
//		{
//			fprintf(stderr, "MessageSender::Popping Message from outMsgs in %d\n",connInfo->getConnectionId());
//			connInfo->pop_outMsgs();
//		}
//
//
//		return SUCCESS;
//	}
//	else
//	{
//		fprintf(stderr, "MessageProcessor:: Ignoring Packet %d. Expecting %d\n",
//						packet.getSeqNo(), out_pkt.getSeqNo());
//		return FAILURE;
//	}
	ConnInfo* connInfo = get_conn_info(packet.getConnId());
	int seqNo = connInfo->getSeqNo();

	assert (packet.getConnId() == connInfo->getConnectionId() || connInfo->getConnectionId() == 0);

	/*	TODO Server gets higher priority when both send packets with the same seq no */
	if((packet.getSeqNo() == seqNo && packet.getType() == ACK) ||
			(packet.getSeqNo() == seqNo + 1 && packet.getType() == DATA))
	{
		/* Pop from conn info */
		if(packet.getSeqNo() == seqNo && packet.getType() == ACK)
		{
			fprintf(stderr, "MessageSender::Popping Message from outMsgs in %d\n",connInfo->getConnectionId());
			connInfo->pop_outMsgs();
		}
		return SUCCESS;
	}
	else
	{
		fprintf(stderr, "MessageProcessor:: Ignoring Packet %d. Expecting %d\n",
						packet.getSeqNo(), seqNo);
		return FAILURE;
	}
}

/**
 * Check if conn ID and Seq Num match the last message in appropriate outbox.
 * Remove from outMsgs.
 * If they do not match, drop the ack packet.
 */
int MessageProcessor::process_incoming_msg(LSP_Packet& packet)
{
	stamp_msg_type(packet);
	stamp_data_type(packet);
	packet.print();

	if(packet.getType() == CONN_REQ) return SUCCESS;

	/* Process ACK packets LATER !! */
	if(packet.getType() == ACK) return SUCCESS;

	if(check_msg_sequence_and_pop_outbox(packet) == SUCCESS)
	{
		ConnInfo* connInfo = get_conn_info(packet.getConnId());
		if(packet.getType() == DATA)
			connInfo->incrementSeqNo();
		return SUCCESS;
	}
	else
		return FAILURE;
}

int MessageProcessor::process_ack_packet(LSP_Packet& packet)
{
	assert (packet.getConnId() > 0);

	return check_msg_sequence_and_pop_outbox(packet);
}


/* Create an ACK packet */
LSP_Packet MessageProcessor::create_ack_packet(LSP_Packet& packet) const
{
	LSP_Packet ack_packet(packet.getConnId(), packet.getSeqNo(), 0, NULL);
	ack_packet.setType(ACK);
	return ack_packet;
}

/* Create a Connection Request */
LSP_Packet MessageProcessor::create_conn_req_packet() const
{
	return LSP_Packet(0, 0, 0, NULL);
}

void MessageProcessor::send_conn_req_packet(char* hostname, char* port)
{
	/* Create a new connection info object for this client */
	ConnInfo *connInfo = new ConnInfo(0, atoi(port), hostname);

	/* Lock before modifying! */
	pthread_mutex_lock (&mutex_connInfos);

	connInfos->push_back(connInfo);

	/* Unlock after modifying! */
	pthread_mutex_unlock (&mutex_connInfos);

	fprintf(stderr, "MessageProcessor:: Pushing Connection Request to outbox. Server %s : %s\n", hostname, port);
	connInfo->add_to_outMsgs(create_conn_req_packet());
}

string MessageProcessor::numToString(int x,int length)
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

MessageProcessor::~MessageProcessor()
{

}
