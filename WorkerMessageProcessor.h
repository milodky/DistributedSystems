#ifndef WORKERMESSAGEPROCESSOR_H
#define WORKERMESSAGEPROCESSOR_H

#include "MessageProcessor.h"

class WorkerMessageProcessor : public MessageProcessor
{
private:
public:
	WorkerMessageProcessor(Inbox* in, vector<ConnInfo*> *infos);
	void process_incoming_msg(LSP_Packet& packet);
	void process_data_packet(LSP_Packet& packet);
	virtual ~WorkerMessageProcessor();
};
#endif
