#ifndef REQUESTMESSAGEPROCESSOR_H
#define REQUESTMESSAGEPROCESSOR_H

#include "MessageProcessor.h"

class RequestMessageProcessor : public MessageProcessor
{
private:
public:
	RequestMessageProcessor(Inbox* in, vector<ConnInfo*> *infos);
	virtual void process_incoming_msg(LSP_Packet& packet);
	virtual void process_data_packet(LSP_Packet& packet);
	virtual int process_ack_packet(LSP_Packet& packet);
	virtual ~RequestMessageProcessor();
};
#endif
