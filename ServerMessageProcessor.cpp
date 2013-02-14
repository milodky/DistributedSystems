#include "ServerMessageProcessor.h"

ServerMessageProcessor::ServerMessageProcessor(Inbox* in, vector<ConnInfo*> *infos,pthread_mutex_t& mutex_connInfos)
	: MessageProcessor(in,infos,mutex_connInfos)
{

}

void ServerMessageProcessor::process_conn_req(LSP_Packet& packet)
{
	fprintf(stderr, "ServerMessageProcessor:: Processing Connection Request from %s : %d\n", packet.getHostname(), packet.getPort());
	/* Create a new connection info object for this client */
	unsigned conn_id = get_next_conn_id();
	ConnInfo *connInfo =
			new ConnInfo(conn_id, packet.getPort(), packet.getHostname());

	/* Lock before modifying! */
    pthread_mutex_lock (&mutex_connInfos);

    connInfos->push_back(connInfo);

    /* Unlock after modifying! */
    pthread_mutex_unlock (&mutex_connInfos);

	/* Send an acknowledgment packet */
	fprintf(stderr, "ServerMessageProcessor:: Pushing ACK packet to Outbox for conn_id: %u\n", conn_id);

	// Need a empty packet to push in the connection ID
	LSP_Packet p(conn_id, 0, 0, NULL);
	LSP_Packet ack_packet = create_ack_packet(p);
	connInfo->add_to_outMsgs(ack_packet);
}

void ServerMessageProcessor::process_incoming_msg(LSP_Packet& packet)
{
	MessageProcessor::process_incoming_msg(packet);
	switch(packet.getType())
	{
	case CONN_REQ:
	{
		process_conn_req(packet);
		break;
	}
	case ACK:
	{
		process_ack_packet(packet);
		break;
	}
	case DATA:
	{
		process_data_packet(packet);
		break;
	}
	default:
		fprintf( stderr, "Unknown Packet Type!\n");
		packet.print();
	}
}

void ServerMessageProcessor::process_data_packet(LSP_Packet& packet)
{

	switch(packet.getDataType())
	{
	case JOINREQUEST:
//		Change conn info isWorker corresponding to conn id as true.
//		A join request can come only from a worker.
		process_join_request_packet(packet);
		break;
	case CRACKREQUEST:
		process_crack_request(packet);
		break;
	case FOUND:
		process_found_packet(packet);
		break;
	case NOTFOUND:
		process_not_found_packet(packet);
		break;
	case ALIVE:
		process_alive_packet(packet);
		break;
	default:
		fprintf( stderr, "Unknown Data Type!\n");
		packet.print();
	}

//write code
//remove msg from outbox, when seqno exceeds that of last message, and packet type not ack.
}

void ServerMessageProcessor::process_crack_request(LSP_Packet& packet)
{
	fprintf(stderr, "ServerMessageProcessor:: Processing crack Request from %s : %d\n", packet.getHostname(), packet.getPort());
//	crack request to server comes from request and is of the format
//	c sha len
//	Send ack to request
	LSP_Packet ack_packet = create_ack_packet(packet);
	ConnInfo* connInfo = get_conn_info(packet.getConnId());
	connInfo->add_to_outMsgs(ack_packet);
	fprintf(stderr, "ServerMessageProcessor:: Pushing ACK packet to Outbox for conn_id: %u\n", packet.getConnId());

//	The server has to split the task equally among all available(non-busy) workers and
//	send crack requests to each worker

	uint8_t* bytes = packet.getBytes();
	string s((char*)bytes);
	stringstream iss(s);
	string ignore;
	iss >> ignore;
	string hash;
	iss >> hash;
	string lengthString;
	iss >> lengthString;
	int length = atoi(lengthString.c_str());
	unsigned workersCount = get_workers_count();
	if(workersCount == 0)
	{
//		Send msg to client that the request cannot be processed
		printf("No resources to process your request!\n");
		return;
	}
	if(length == 0)
	{
//		Send msg to client that the request was faulty.
		printf("The password to be found cannot be of length 0");
		return;
	}
	if(length>5)
	{
//		Send msg to client that the password is too long. Cannot process.
		return;
	}
	if(length<4)
	{
//		Assign only 1 worker. Sending message to more workers will take more time
//		than processing by a single worker for 17576 entries.

		ConnInfo* cInfo;
		for(vector<ConnInfo*>::iterator it=connInfos->begin();
						it!=connInfos->end(); ++it)
		{
			if((*it)->isIsAlive() && (*it)->isIsWorker())
			{
				cInfo = (*it);
				break;
			}
		}
		int end = pow(26,length);
		std::ostringstream sin;
        sin << end;
        string endString = sin.str();
	    string data = "c " + hash + " 0" + "  " +endString;
//	    Add entry in map.
	    WorkerInfo w(cInfo->getConnectionId(), 0, 0, end);
	    int connId = packet.getConnId();
//	    There can only be one request from a particular client.
	    assert(clientWorkerInfo.find(connId)==clientWorkerInfo.end());
		vector<WorkerInfo> workers;
		workers.push_back(w);
		clientWorkerInfo[connId] = workers;
//		Add connId of client to workers' clients queue.
		cInfo->pushClients(connId);
//		Send crack request to worker.
		send_crack_worker_request(cInfo, data.c_str());
	}
	else if(length > 4)
	{
		int start = 0;
		int numPoss = pow(26,length);
		int each = ceil(numPoss/workersCount);
		for(vector<ConnInfo*>::iterator it=connInfos->begin();
								it!=connInfos->end(); ++it)
		{
			if((*it)->isIsAlive() && (*it)->isIsWorker())
			{
				ConnInfo* cInfo = (*it);
				std::ostringstream sin;
				sin << start;
				string startString = sin.str();
				int last;
				if(start+each>numPoss)
					last = 	numPoss;
				else
					last = 	start+each;
				sin << last;
				string endString = sin.str();
				string data = "c " + hash + " "  + startString + "  " +endString;
//	    		Add entry in map
			    WorkerInfo w(cInfo->getConnectionId(), 0,start, last);
			    int connId = packet.getConnId();
				if(clientWorkerInfo.find(connId)==clientWorkerInfo.end())
				{
					vector<WorkerInfo> workers;
					workers.push_back(w);
					clientWorkerInfo[connId] = workers;
				}
				else
				{
					clientWorkerInfo[connId].push_back(w);
				}
//				Add connId of client to workers' clients queue.
				cInfo->pushClients(connId);
//				Send crack request to worker.
				send_crack_worker_request(cInfo, data.c_str());
				start = start + each + 1;
			}
		}
	}
}


void ServerMessageProcessor::process_join_request_packet(LSP_Packet& packet)
{
	fprintf(stderr, "ServerMessageProcessor:: Processing Join Request from %s : %d\n", packet.getHostname(), packet.getPort());
	ConnInfo* cInfo = get_conn_info(packet.getConnId());
	cInfo->setIsWorker(true);
	assert(cInfo->isIsWorker() == true);
	LSP_Packet ack_packet = create_ack_packet(packet);
	cInfo->add_to_outMsgs(ack_packet);
	fprintf(stderr, "ServerMessageProcessor:: Pushing ACK packet to Outbox for conn_id: %u\n", packet.getConnId());
}


void ServerMessageProcessor::process_found_packet(LSP_Packet& packet)
{
	fprintf(stderr, "ServerMessageProcessor:: Processing Found Request from %s : %d\n", packet.getHostname(), packet.getPort());
//	Payload of form
//	f pass
	ConnInfo* cInfo = get_conn_info(packet.getConnId());
//	Send ack to worker. This can come to server only from a worker.
	assert(cInfo->isIsWorker() == true);
	LSP_Packet ack_packet = create_ack_packet(packet);
	cInfo->add_to_outMsgs(ack_packet);
	fprintf(stderr, "ServerMessageProcessor:: Pushing ACK packet to Outbox for conn_id: %u\n", packet.getConnId());
//	Remove map entry.
	int clientId = cInfo->popClients();
	assert(clientWorkerInfo.find(clientId)!=clientWorkerInfo.end());
	clientWorkerInfo.erase(clientId);
//	Send result to client.
	ConnInfo* conInfo = get_conn_info(clientId);
	LSP_Packet client_packet(clientId,conInfo->getSeqNo(),packet.getLen(),packet.getBytes());
	conInfo->add_to_outMsgs(client_packet);
}

void ServerMessageProcessor::process_not_found_packet(LSP_Packet& packet)
{
	fprintf(stderr, "ServerMessageProcessor:: Processing Not Found Request from %s : %d\n", packet.getHostname(), packet.getPort());
//	Update map entry. If all have returned 'not found', send message to client,
//	remove map entry.
	ConnInfo* cInfo = get_conn_info(packet.getConnId());
//	Send ack to worker. This can come to server only from a worker.
	assert(cInfo->isIsWorker() == true);
	LSP_Packet ack_packet = create_ack_packet(packet);
	cInfo->add_to_outMsgs(ack_packet);
	fprintf(stderr, "ServerMessageProcessor:: Pushing ACK packet to Outbox for conn_id: %u\n", packet.getConnId());
//	Update map entry.
	int clientId = cInfo->popClients();

//	If clientId not in maps keys, it means that one of the workers
//	has already found the password.
//	Update seq number and return
	vector<WorkerInfo> &workers = clientWorkerInfo[clientId];
	if(clientWorkerInfo.find(clientId) == clientWorkerInfo.end())
	{
		cInfo->incrementSeqNo();
		return;
	}
//	Update processing status of this worker.
	for(vector<WorkerInfo>::iterator it=workers.begin();
						it!=workers.end(); ++it)
	{
		if((*it).getConnId() == packet.getConnId())
		{
			(*it).setProcessingStatus(-1);
			break;
		}
	}
//	If all workers have -1 as processing status, send a message to client
//	as message not found. Format is
//	x
	bool stillProcessing = false;
	for(vector<WorkerInfo>::iterator it=workers.begin();
							it!=workers.end(); ++it)
	{
		if((*it).getProcessingStatus() == -1)
		{
			continue;
		}
		else
		{
			stillProcessing = true;
		}
	}
	if(!stillProcessing)
	{
		ConnInfo* conInfo = get_conn_info(clientId);
		uint8_t* bytes = (uint8_t*)"x";
		LSP_Packet client_packet(clientId,conInfo->getSeqNo(),2,bytes);
		conInfo->add_to_outMsgs(client_packet);
//		Remove entry from map.
	}
}

void ServerMessageProcessor::process_alive_packet(LSP_Packet& packet)
{
	fprintf(stderr, "ServerMessageProcessor:: Processing Alive Request from %s : %d\n", packet.getHostname(), packet.getPort());
	ConnInfo* cInfo = get_conn_info(packet.getConnId());
//	Send ack packet.
	LSP_Packet ack_packet = create_ack_packet(packet);
	cInfo->add_to_outMsgs(ack_packet);
	fprintf(stderr, "ServerMessageProcessor:: Pushing ACK packet to Outbox for conn_id: %u\n", packet.getConnId());
//	Update seq no
	cInfo->incrementSeqNo();

}
unsigned ServerMessageProcessor::get_workers_count()
{
	unsigned count =0;
	for(vector<ConnInfo*>::iterator it=connInfos->begin();
					it!=connInfos->end(); ++it)
	{
		if((*it)->isIsAlive() && (*it)->isIsWorker())
			++count;
	}
	return count;
}

unsigned ServerMessageProcessor::get_next_conn_id() const
{
	return connInfos->size() + 1;
}

void ServerMessageProcessor::send_crack_worker_request(ConnInfo* cInfo,const char* hash)
{
//	The crack request that the server sends to the worker will have the format
//	c hash lower upper
	LSP_Packet packet(cInfo->getConnectionId(), cInfo->getSeqNo(),strlen(hash), (uint8_t*)hash);
	cInfo->add_to_outMsgs(packet);
}

ServerMessageProcessor::~ServerMessageProcessor()
{

}
