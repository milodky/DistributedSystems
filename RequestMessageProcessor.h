#ifndef REQUESTMESSAGEPROCESSOR_H
#define REQUESTMESSAGEPROCESSOR_H

#include "MessageProcessor.h"

class RequestMessageProcessor : public MessageProcessor
{
private:
	const char* hashMsg;
	unsigned password_length;

public:
	RequestMessageProcessor(Inbox* in, vector<ConnInfo*> *infos, pthread_mutex_t& mutex_connInfos);

	virtual int process_incoming_msg(LSP_Packet& packet);
	virtual void process_data_packet(LSP_Packet& packet);
	virtual int process_ack_packet(LSP_Packet& packet);

	void set_password_data(const char* const hashMsg, const unsigned len);

	LSP_Packet create_crack_req_packet();

	virtual ~RequestMessageProcessor();
};
#endif
