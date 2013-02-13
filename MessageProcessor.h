#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H

#include "header.h"
#include "lsppacket.h"
#include "inbox.h"
#include "connectionInfo.h"

class MessageProcessor : public Uncopyable
{
protected:
	Inbox* inbox;
	vector<ConnInfo*> *connInfos;

public:
	MessageProcessor(Inbox* in, vector<ConnInfo*> *infos);

	int poll_inbox();

	/* Process incoming Packet */
	virtual void process_incoming_msg(LSP_Packet& packet);

	/* Process a data packet */
	virtual void process_data_packet(LSP_Packet& packet) = 0;

	/* Figure out the packet type and stamp it on the packet object */
	void stamp_msg_type(LSP_Packet& packet);

	/* Figure out the data type and stamp it on the packet object */
	void stamp_data_type(LSP_Packet& packet);

	/* Process an acknowledgment packet */
	void process_ack_packet(LSP_Packet& packet);

	/* Create an ACK packet */
	LSP_Packet create_ack_packet(LSP_Packet& packet) const;

	virtual ~MessageProcessor();
};

#endif
