#ifndef SERVERMESSAGEPROCESSOR_H
#define SERVERMESSAGEPROCESSOR_H

#include "MessageProcessor.h"
#include <sstream>
#include <math.h>
#include <stdlib.h>

class WorkerInfo
{
	int connId;
	int processingStatus; //0 - processing, 1 - found, -1 - not found
	int start;
	int end;
};
class Task
{
	int cId;
	char* hash;
	int len;
};
class ServerMessageProcessor : public MessageProcessor
{
private:
	map<Task, vector<WorkerInfo> > clientWorkerInfo;
public:
	ServerMessageProcessor(Inbox* in, vector<ConnInfo*> *infos);

	/* Process incoming Packet */
	virtual void process_incoming_msg(LSP_Packet& packet);

	void send_crack_worker_request(ConnInfo* cInfo,const char* hash);

	/* Process a join request */
	void process_join_request_packet(LSP_Packet& packet);

	void process_crack_request(LSP_Packet& packet);

	void process_found_packet(LSP_Packet& packet);

	void process_not_found_packet(LSP_Packet& packet);

	/* Process a data packet */
	virtual void process_data_packet(LSP_Packet& packet);

	/* Process a connection request packet */
	void process_conn_req(LSP_Packet& packet);

	/* Get the connection ID to be set for a new Connection Request */
	unsigned get_next_conn_id() const;

	unsigned get_workers_count();

	virtual ~ServerMessageProcessor();
};

#endif
