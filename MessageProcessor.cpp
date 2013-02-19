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
//		fprintf(stderr, "MessageProcessor:: Received Packet. \n");
		if(process_incoming_msg(packet) == COMPLETE)
			break;
		sleep(0);
	}
	return COMPLETE;
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
		if((*it)->getConnectionId() == connId) return (*it);
	}

	fprintf(stderr, "MessageProcessor::No connInfo object for connId: %d\n", connId);
	return NULL;
}

int MessageProcessor::check_msg_sequence_and_pop_outbox(LSP_Packet& packet)
{
	ConnInfo* connInfo = get_conn_info(packet.getConnId());
	if(connInfo == NULL)
	{
		fprintf(stderr, "MessageProcessor:: Ignoring Packet.\n");
		return FAILURE;
	}

	/**
	 * Since a valid connection info object exists! reset epoch count.
	 * process on the other end is alive!
	 */
	connInfo->resetEpochCount();

	int seqNo = connInfo->getSeqNo();

	assert (packet.getConnId() == connInfo->getConnectionId() || connInfo->getConnectionId() == 0);

	/*	TODO Server gets higher priority when both send packets with the same seq no */
	if((packet.getSeqNo() == seqNo && packet.getType() == ACK) ||
			(packet.getSeqNo() == seqNo + 1 && packet.getType() == DATA))
	{
		/* Pop from conn info */
		/**
		 * Always pop!
		 * case 1> We sent a data packet and it has been ack ed
		 * case 2> We sent an ack packet and now we have received data
		 * case 3 and 4 ??
		 */
//		fprintf(stderr, "MessageProcessor::Popping Outbox for conn_id: %d\n",
//				connInfo->getConnectionId());
		if (connInfo->ConnInfo::getOutMsgsCount() > 0)
			connInfo->pop_outMsgs();
		return SUCCESS;
	}
	else if(packet.getType() == ACK)
	{
//		fprintf(stderr, "MessageProcessor:: conn_id: %d Ignoring ACK Packet seq: %d. Expecting %d\n",
//				connInfo->getConnectionId(), packet.getSeqNo(), seqNo);
	}
	else if(packet.getType() == DATA)
	{
		fprintf(stderr, "MessageProcessor:: conn_id: %d Ignoring Data Packet seq: %d. Expecting %d\n",
				connInfo->getConnectionId(), packet.getSeqNo(), seqNo + 1);
	}
	return FAILURE;
}

/**
 * Check if conn ID and Seq Num match the last message in appropriate outbox.
 * Remove from outMsgs.
 * If they do not match, drop the ack packet.
 */
int MessageProcessor::process_incoming_msg(LSP_Packet& packet)
{
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

LSP_Packet MessageProcessor::create_not_found_packet(ConnInfo *connInfo)
{
	unsigned data_length = 2;
	connInfo->incrementSeqNo();

	uint8_t* data = new uint8_t[data_length];
	data[0] = 'x';
	data[1] = '\0';

	LSP_Packet c_pkt(
			connInfo->getConnectionId(),
			connInfo->getSeqNo(),
			data_length,
			data);

	delete data;
	return c_pkt;
}

MessageProcessor::~MessageProcessor()
{

}
