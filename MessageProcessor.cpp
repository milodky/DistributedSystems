#include "MessageProcessor.h"

MessageProcessor::MessageProcessor(Inbox* in, vector<ConnInfo*> *infos)
	: inbox(in), connInfos(infos)
{

}

int MessageProcessor::poll_inbox()
{
	while(true)
	{
		/* Empty Inbox: Life is chill! :-) */
		if(inbox->isEmpty()) continue;

		LSP_Packet packet = inbox->pop_msg();

		process_incoming_msg(packet);
	}
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
		fprintf( stderr, "Unknown Packet Type!\n");
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
	stamp_msg_type(packet);
	switch(packet.getType())
	{
	case CONN_REQ:
		process_conn_req(packet);
		break;
	case ACK:
		break;
	case DATA:
	{
		switch(packet.getDataType())
		{
		case JOINREQUEST:
			break;
		case CRACKREQUEST:
			break;
		case FOUND:
			break;
		case NOTFOUND:
			break;
		case ALIVE:
			break;
		default:
			fprintf( stderr, "Unknown Data Type!\n");
			packet.print();
		}
	}
	default:
		fprintf( stderr, "Unknown Packet Type!\n");
		packet.print();
	}
}

void MessageProcessor::process_conn_req(LSP_Packet& packet)
{
	/* Create a new connection info object for this client */
	unsigned conn_id = get_next_conn_id();
	ConnInfo *connInfo =
			new ConnInfo(conn_id, packet.getPort(), packet.getHostname());

	connInfos->push_back(connInfo);

	/* Send an acknowledgment packet */
	LSP_Packet ack_packet = create_ack_packet(packet);
	connInfo->add_to_outMsgs(ack_packet);
}

void MessageProcessor::process_ack_packet(LSP_Packet& packet)
{
//remove msg from outbox
}

void MessageProcessor::process_data_packet(LSP_Packet& packet)
{
//write code
//remove msg from outbox, when seqno exceeds that of last message, and packet type not ack.
}

/* Create an ACK packet */
LSP_Packet MessageProcessor::create_ack_packet(LSP_Packet& packet) const
{
	return LSP_Packet(packet.getConnId(), packet.getSeqNo(), 0, NULL);
}

unsigned MessageProcessor::get_next_conn_id() const
{
	return connInfos->size() + 1;
}

MessageProcessor::~MessageProcessor()
{

}
