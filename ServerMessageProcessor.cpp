#include "ServerMessageProcessor.h"

ServerMessageProcessor::ServerMessageProcessor(Inbox* in, vector<ConnInfo*> *infos)
	: MessageProcessor(in, infos)
{

}

void ServerMessageProcessor::process_conn_req(LSP_Packet& packet)
{
	fprintf(stderr, "ServerMessageProcessor:: Processing Connection Request from %s : %d\n", packet.getHostname(), packet.getPort());
	/* Create a new connection info object for this client */
	unsigned conn_id = get_next_conn_id();
	ConnInfo *connInfo =
			new ConnInfo(conn_id, packet.getPort(), packet.getHostname());

	connInfos->push_back(connInfo);

	/* Send an acknowledgment packet */
	fprintf(stderr, "ServerMessageProcessor:: Pushing ACK packet to Outbox for conn_id: %u\n", conn_id);

	// Need a dummy packet to push in the connection ID
	LSP_Packet p(conn_id, 0, 0, NULL);
	LSP_Packet ack_packet = create_ack_packet(p);
	connInfo->add_to_outMsgs(ack_packet);
}

void ServerMessageProcessor::process_incoming_msg(LSP_Packet& packet)
{
	MessageProcessor::process_incoming_msg(packet);
	switch(packet.getType())
	{
	case CONN_REQ:
		process_conn_req(packet);
		break;
	case ACK:
		break;
	case DATA:
		process_data_packet(packet);
		break;
	default:
		fprintf( stderr, "Unknown Packet Type!\n");
		packet.print();
	}
}

void ServerMessageProcessor::process_data_packet(LSP_Packet& packet)
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

//write code
//remove msg from outbox, when seqno exceeds that of last message, and packet type not ack.
}

unsigned ServerMessageProcessor::get_next_conn_id() const
{
	return connInfos->size() + 1;
}

ServerMessageProcessor::~ServerMessageProcessor()
{

}
