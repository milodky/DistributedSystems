#include <openssl/sha.h>
#include <sstream>

#include "WorkerMessageProcessor.h"

using namespace std;

void* processor_run(void* arg)
{
	struct ThData* params = (ThData *) arg;
	fprintf(stderr, "LSP:: Running Processor Thread...\n");
	params->worker_instance->runProcessor();
	delete params;
}

Data::Data( const char* s, int st, int e, int l, ConnInfo *connInfo):
		sha(s),start(st),end(e),length(l),cInfo(connInfo)
{

}

WorkerMessageProcessor::WorkerMessageProcessor(Inbox* in, vector<ConnInfo*> *infos, pthread_mutex_t& mutex_connInfos)
	: MessageProcessor(in,infos, mutex_connInfos)
{
	start_processor_thread();
}

int WorkerMessageProcessor::process_incoming_msg(LSP_Packet& packet)
{
	if(MessageProcessor::process_incoming_msg(packet) == FAILURE)
		return FAILURE;
	switch(packet.getType())
	{
	case ACK:
		process_ack_packet(packet);
		break;
	case DATA:
		process_data_packet(packet);
		break;
	default:
		fprintf( stderr, "Unknown Packet Type!\n");
		packet.print();
	}
	return SUCCESS;
}

int WorkerMessageProcessor::process_ack_packet(LSP_Packet& packet)
{
//  If seq number is 0, send join request to server.
//  Payload will be 'j'
	ConnInfo* connInfo = get_conn_info();

	/* Set the connection ID */
	if(	connInfo->getConnectionId() == 0 && connInfo->getSeqNo() == 0)
	{
		connInfo->setConnectionId(packet.getConnId());
	}
	if(MessageProcessor::process_ack_packet(packet) == FAILURE)
		return FAILURE;

	/* Special Handling: Send Crack Request to Server */
	if(	connInfo->getSeqNo() == 0)
	{
		fprintf( stderr, "WorkerMessageProcessor::Pushing JOIN REQUEST to outbox\n");
		connInfo->incrementSeqNo();
		LSP_Packet j_pkt = create_join_req_packet();
		connInfo->add_to_outMsgs(j_pkt);
	}

	return SUCCESS;
}

/**
 * Create a crack request Data:
 * byte[0] = 'c', byte[1] = len, following bytes = hash
 */
LSP_Packet WorkerMessageProcessor::create_join_req_packet()
{
	ConnInfo* connInfo = get_conn_info();

	unsigned data_length = 1;

	uint8_t* data = new uint8_t[data_length];
	data[0] = 'j';

	LSP_Packet c_pkt(
			connInfo->getConnectionId(),
			connInfo->getSeqNo(),
			data_length,
			data);

	delete data;
	return c_pkt;
}



int WorkerMessageProcessor::process_data_packet(LSP_Packet& packet)
{
	switch(packet.getDataType())
	{
	case CRACKREQUEST:
		process_crack_request(packet);
		break;
	default:
		fprintf( stderr, "Unknown Data Type!\n");
		packet.print();
	}
	return SUCCESS;
}

void WorkerMessageProcessor::process_crack_request(LSP_Packet& packet)
{
//		Update seq number. If outbox has any msg with sequence number less than
//		current, remove from outbox. This case will only happen when server
//		sends a crack request after the worker sends an 'Alive' message,
//		but before the server gets it.

//	This comes from the server and has the following format:
//	c hash lower upper
	fprintf(stderr, "WorkerMessageProcessor:: Received crack request from server.\n");
	uint8_t* bytes = packet.getBytes();
	string s((char*)bytes);
	stringstream iss(s);
	string ignore;
	iss >> ignore;
	string hash;
	iss >> hash;
	string startString;
	iss >> startString;
	int start = strToNum(startString);
	string endString;
	iss >> endString;
	int end = strToNum(endString);
	int length = strlen(startString.c_str());
	//	Send an ack
	ConnInfo* cInfo = get_conn_info();

	LSP_Packet ack_packet = create_ack_packet(packet);
	cInfo->add_to_outMsgs(ack_packet);
	//Push into queue
	Data *request = new Data(hash.c_str(), start, end, length, cInfo);
	processQueue.push(request);
	//process_crack_request(hash.c_str(), start, end, length, cInfo);
}

void WorkerMessageProcessor::process_crack_request(const char* sha, int start, int end, int length, ConnInfo *cInfo)
{
	bool found = false;
	for(int i = start; i <= end; i++)
	{
		string str = numToString(i,length);
		char buf[SHA_DIGEST_LENGTH*2];
		getSHA(str.c_str(),buf);
		if(strcmp(sha,buf)==0)
		{
			found = true;
			LSP_Packet c_pkt(create_found_packet(str));
			cInfo->add_to_outMsgs(c_pkt);
			printf("Found: %s\n",str.c_str());
		}
	}
	if(!found)
	{
		ConnInfo* connInfo = get_conn_info();
		LSP_Packet c_pkt(create_not_found_packet(connInfo));
		cInfo->add_to_outMsgs(c_pkt);
		printf("Not Found\n");
	}
}

LSP_Packet WorkerMessageProcessor::create_found_packet(string str)
{
	ConnInfo* connInfo = get_conn_info();
	connInfo->incrementSeqNo();
	uint8_t data[20];
	sprintf((char*) data, "f %s", str.c_str());
	unsigned data_length = strlen((char*)data) + 1;

	LSP_Packet c_pkt(
			connInfo->getConnectionId(),
			connInfo->getSeqNo(),
			data_length,
			data);

	return c_pkt;
}

int WorkerMessageProcessor::strToNum(string x)
{
	int sum = 0;
	int length = strlen(x.c_str());
	for(int i=0;i<length;i++)
	{
		char a = x[i] - 'a';
		sum += int(a)*pow(26,(length-i-1));
	}
	return sum;
}

void WorkerMessageProcessor::getSHA(const char* str, char* sha)
{
	int i = 0;
	unsigned char temp[SHA_DIGEST_LENGTH];

	memset(sha, 0x0, SHA_DIGEST_LENGTH*2);
	memset(temp, 0x0, SHA_DIGEST_LENGTH);

	SHA1((unsigned char *)str, strlen(str), temp);

	for (i=0; i < SHA_DIGEST_LENGTH; i++) {
		sprintf((char*)&(sha[i*2]), "%02x", temp[i]);
	}
}

void WorkerMessageProcessor::start_processor_thread()
{
	int e;
	ThData *data = new ThData();
	data->worker_instance = this;
	if (e = pthread_create(&processor_thread, &attr, processor_run, (void *) data))
		Error("pthread_create %d", e);
}

void WorkerMessageProcessor::runProcessor()
{
	while(1)
	{
		if(processQueue.size()!=0)
		{
			Data *d = processQueue.front();
			process_crack_request(d->sha, d->start, d->end, d->length, d->cInfo);
			delete d;
			processQueue.pop();
		}
		sleep(0);
	}
}


WorkerMessageProcessor::~WorkerMessageProcessor()
{

}
