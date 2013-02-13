#ifndef REQUESTMESSAGEPROCESSOR_H
#define REQUESTMESSAGEPROCESSOR_H

#include "MessageProcessor.h"

class RequestMessageProcessor : public MessageProcessor
{
private:
public:
	RequestMessageProcessor(Inbox* in, vector<ConnInfo*> *infos);
	void process_incoming_msg(LSP_Packet& packet);
	void process_data_packet(LSP_Packet& packet);
	virtual ~RequestMessageProcessor();
};
#endif
