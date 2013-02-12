#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H

#include "header.h"
#include "lsppacket.h"
#include "inbox.h"

class MessageProcessor : public Uncopyable
{
private:
	Inbox* inbox;
	vector<ConnInfo*> *connInfos;

public:
	MessageProcessor(Inbox* in, vector<ConnInfo*> *infos);

	int poll_inbox();

	/* Process incoming Packet */
	void process_incoming_msg(LSP_Packet& packet);

	/* Figure out the packet type and stamp it on the packet object */
	void stamp_msg_type(LSP_Packet& packet);

	/* Process a connection request packet */
	void process_conn_req(LSP_Packet& packet);

	/* Process an acknowledgment packet */
	void process_ack_packet(LSP_Packet& packet);

	/* Create an ACK packet */
	LSP_Packet create_ack_packet(LSP_Packet& packet) const;

	/* Get the connection ID to be set for a new Connection Request */
	unsigned get_next_conn_id() const;

	~MessageProcessor();
};

#endif
