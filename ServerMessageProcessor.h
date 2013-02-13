#ifndef SERVERMESSAGEPROCESSOR_H
#define SERVERMESSAGEPROCESSOR_H

#include "MessageProcessor.h"

class ServerMessageProcessor : public MessageProcessor
{
private:
public:
	ServerMessageProcessor(Inbox* in, vector<ConnInfo*> *infos);

	/* Process incoming Packet */
	virtual void process_incoming_msg(LSP_Packet& packet);

	/* Process a data packet */
	virtual void process_data_packet(LSP_Packet& packet) = 0;

	/* Process a connection request packet */
	void process_conn_req(LSP_Packet& packet);

	/* Get the connection ID to be set for a new Connection Request */
	unsigned get_next_conn_id() const;

	virtual ~ServerMessageProcessor();
};

#endif
