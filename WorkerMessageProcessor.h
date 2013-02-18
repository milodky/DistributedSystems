#ifndef WORKERMESSAGEPROCESSOR_H
#define WORKERMESSAGEPROCESSOR_H

#include "MessageProcessor.h"

class WorkerMessageProcessor : public MessageProcessor
{
private:
public:
	WorkerMessageProcessor(Inbox* in, vector<ConnInfo*> *infos, pthread_mutex_t& mutex_connInfos);

	virtual int process_incoming_msg(LSP_Packet& packet);
	virtual int process_data_packet(LSP_Packet& packet);
	virtual int process_ack_packet(LSP_Packet& packet);

	void process_crack_request(LSP_Packet& packet);
	LSP_Packet process_crack_request(const char* sha, int start, int end, int length);
	int strToNum(string x);
	void getSHA(const char* str, char* sha);

	LSP_Packet create_join_req_packet();
	LSP_Packet create_found_packet(string str);

	virtual ~WorkerMessageProcessor();
};
#endif
