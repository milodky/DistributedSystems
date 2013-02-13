#include "MessageProcessor.h"

MessageProcessor::MessageProcessor(Inbox* in, vector<ConnInfo*> *infos)
	: inbox(in), connInfos(infos)
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
		if((*it)->connectionID == connId)
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

void MessageProcessor::process_incoming_msg(LSP_Packet& packet)
{
	stamp_msg_type(packet);
	stamp_data_type(packet);
	packet.print();
}

/**
 * Check if conn ID and Seq Num match the last message in appropriate outbox.
 * Remove from outMsgs.
 * If they do not match, drop the ack packet.
 */
int MessageProcessor::process_ack_packet(LSP_Packet& packet)
{
	assert (packet.getConnId() > 0);

	ConnInfo* connInfo;
	LSP_Packet out_pkt = connInfo->get_front_msg();

	assert (packet.getConnId() == out_pkt.getConnId());
	if(packet.getSeqNo() != out_pkt.getSeqNo())
	{
		fprintf(stderr, "MessageProcessor:: Ignoring ACK Packet %d. Expecting %d\n",
				packet.getSeqNo(), out_pkt.getSeqNo());
		return FAILURE;
	}

	/* Pop from conn info */
	connInfo->pop_outMsgs();

	return SUCCESS;
}


/* Create an ACK packet */
LSP_Packet MessageProcessor::create_ack_packet(LSP_Packet& packet) const
{
	return LSP_Packet(packet.getConnId(), packet.getSeqNo(), 0, NULL);
}

/* Create a Connection Request */
LSP_Packet MessageProcessor::create_conn_req_packet() const
{
	return LSP_Packet(0, 0, 0, NULL);
}

void MessageProcessor::send_conn_req_packet(char* hostname, char* port)
{
	/* Create a new connection info object for this client */
	ConnInfo *connInfo = new ConnInfo(-1, atoi(port), hostname);

	connInfos->push_back(connInfo);

	fprintf(stderr, "MessageProcessor:: Pushing Connection Request to outbox. Server %s : %s\n", hostname, port);
	connInfo->add_to_outMsgs(create_conn_req_packet());
}

MessageProcessor::~MessageProcessor()
{

}
