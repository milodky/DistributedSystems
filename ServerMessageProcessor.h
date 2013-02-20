#ifndef SERVERMESSAGEPROCESSOR_H
#define SERVERMESSAGEPROCESSOR_H

#include "MessageProcessor.h"
#include <sstream>
#include <stdlib.h>

class WorkerInfo
{
	int connId;
	int processingStatus; //0 - processing, 1 - found, -1 - not found
	string hash;
	string start;
	string end;
public:
	WorkerInfo(int cId, int pStatus,string h, string s, string e):
		connId(cId), processingStatus(pStatus), hash(h), start(s),end(e)
{}
	WorkerInfo& operator = (const WorkerInfo& that);
	WorkerInfo(const WorkerInfo& that);

	int getConnId() const {
		return connId;
	}

	void setConnId(int connId) {
		this->connId = connId;
	}

	string getEnd() const {
		return end;
	}

	void setEnd(string end) {
		this->end = end;
	}

	int getProcessingStatus() const {
		return processingStatus;
	}

	void setProcessingStatus(int processingStatus) {
		this->processingStatus = processingStatus;
	}

	string getStart() const {
		return start;
	}

	void setStart(string start) {
		this->start = start;
	}

	string getHash() const {
		return hash;
	}

	void setHash(string hash) {
		this->hash = hash;
	}
};

class ServerMessageProcessor : public MessageProcessor
{
private:
	map<int, vector<WorkerInfo> > clientWorkerInfo;
public:
	ServerMessageProcessor(Inbox* in, vector<ConnInfo*> *infos, pthread_mutex_t& mutex_connInfos);

	/* Process incoming Packet */
	virtual int process_incoming_msg(LSP_Packet& packet);

	void send_crack_worker_request(LSP_Packet & packet, ConnInfo* cInfo, WorkerInfo& w, const char* hash);

	/* Process a join request */
	void process_join_request_packet(LSP_Packet& packet);

	void process_crack_request(LSP_Packet& packet);

	void process_found_packet(LSP_Packet& packet);

	void process_not_found_packet(LSP_Packet& packet);

	void process_alive_packet(LSP_Packet& packet);

	void send_not_found_packet(int clientId);

	/* Process a data packet */
	virtual int process_data_packet(LSP_Packet& packet);

	bool check_conn_req_validity(LSP_Packet& packet);

	/* Process a connection request packet */
	void process_conn_req(LSP_Packet& packet);

	/* Get the connection ID to be set for a new Connection Request */
	unsigned get_next_conn_id() const;

	unsigned get_workers_count();

	vector<int> get_least_busy_workers(int count);

	void reassignWork(ConnInfo *c);

	virtual ~ServerMessageProcessor();
};

#endif
