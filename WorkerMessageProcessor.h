#ifndef WORKERMESSAGEPROCESSOR_H
#define WORKERMESSAGEPROCESSOR_H

#include "MessageProcessor.h"

class WorkerMessageProcessor : public MessageProcessor
{
private:
public:
	WorkerMessageProcessor(Inbox* in, vector<ConnInfo*> *infos);

	virtual void process_incoming_msg(LSP_Packet& packet);
	virtual void process_data_packet(LSP_Packet& packet);
	virtual int process_ack_packet(LSP_Packet& packet);

	void process_crack_request(LSP_Packet& packet);
	void process_crack_request(string sha, int start, int end, int length, char* password);
	string numToString(int x,int length);

	LSP_Packet create_join_req_packet();

	virtual ~WorkerMessageProcessor();
};
#endif
