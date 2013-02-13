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
	virtual void process_ack_packet(LSP_Packet& packet);
	void process_crack_request(LSP_Packet& packet);
	void process_crack_request(string sha, int start, int count, int length, char* password);
	void process_crack_request(uint8_t* sha, uint8_t* start, uint8_t* count, uint8_t* length, char* password);
	string numToString(int x,int length);
	virtual ~WorkerMessageProcessor();
};
#endif
