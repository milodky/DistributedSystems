#ifndef WORKERMESSAGEPROCESSOR_H
#define WORKERMESSAGEPROCESSOR_H

#include "MessageProcessor.h"

/* A helper structure for the thread  */
struct ThData
{
	WorkerMessageProcessor* worker_instance;
};

/* A structure to support pthreads in c++ */
struct Data : public Uncopyable
{
	const char* sha;
	int start;
	int end;
	int length;
	ConnInfo *cInfo;
	Data( const char* sha, int start, int end, int length, ConnInfo *cInfo);
};

class WorkerMessageProcessor : public MessageProcessor
{
private:
	/* A thread to continuosly poll to check if there are any new requests from the server */
	pthread_t processor_thread;
	pthread_attr_t attr;
	/* A queue into which multiple requests from the server will be maintained */
	queue<Data*> processQueue;
public:
	WorkerMessageProcessor(Inbox* in, vector<ConnInfo*> *infos, pthread_mutex_t& mutex_connInfos);
	/* A wrapper to process any incoming message */
	virtual int process_incoming_msg(LSP_Packet& packet);
	/* Actions to be taken on receiving a data packet */
	virtual int process_data_packet(LSP_Packet& packet);
	/* Actions to be taken on receiving an ack packet */
	virtual int process_ack_packet(LSP_Packet& packet);
	/* Functions to start the thread */
	void runProcessor();	
	void start_processor_thread();

	/* Actions to be taken on receiving a crack request packet */
	void process_crack_request(LSP_Packet& packet);
	/* A helper function that will add the new request into processQueue */
	void process_crack_request(const char* sha, int start, int end, int length, ConnInfo *connInfo);
	/* Helper functions for cracking the request */
	int strToNum(string x);
	void getSHA(const char* str, char* sha);

	/* Creating a join request packet to be sent to the server */
	LSP_Packet create_join_req_packet();
	/* Creating a found packet to be sent to the server */
	LSP_Packet create_found_packet(string str);

	virtual ~WorkerMessageProcessor();
};
#endif
