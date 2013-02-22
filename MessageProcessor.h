#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H

#include <string>

#include "header.h"
#include "lsppacket.h"
#include "inbox.h"
#include "connectionInfo.h"

class MessageProcessor : public Uncopyable
{
protected:
	Inbox* inbox;
	pthread_mutex_t& mutex_connInfos;
	vector<ConnInfo*> *connInfos;

public:
	bool testing;

	MessageProcessor(Inbox* in, vector<ConnInfo*> *infos, pthread_mutex_t& mutex_connInfos);

	int poll_inbox();

	ConnInfo* get_conn_info();

	ConnInfo* get_conn_info(int);

	/* Process incoming Packet */
	virtual int process_incoming_msg(LSP_Packet& packet);

	/* Process a data packet */
	virtual int process_data_packet(LSP_Packet& packet) = 0;

	int check_msg_sequence_and_pop_outbox(LSP_Packet& packet);

	/* Process an acknowledgment packet */
	virtual int process_ack_packet(LSP_Packet& packet);

	/* Create an ACK packet */
	LSP_Packet create_ack_packet(LSP_Packet& packet) const;

	/* Create a Connection Request */
	LSP_Packet create_conn_req_packet() const;

	/* Send a Connection Request */
	void send_conn_req_packet(char* hostname, char* port);

	/* Convert from a number to a string of length */
	string numToString(int x, int length);

	LSP_Packet create_not_found_packet(ConnInfo *connInfo);

	virtual ~MessageProcessor();
	Inbox* getInbox();
};


#endif
