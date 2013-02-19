#include "ServerMessageProcessor.h"

ServerMessageProcessor::ServerMessageProcessor(
		Inbox* in, vector<ConnInfo*> *infos,
		pthread_mutex_t& mutex_connInfos)
	: MessageProcessor(in,infos,mutex_connInfos)
{

}

bool ServerMessageProcessor::check_conn_req_validity(LSP_Packet& packet)
{
	bool return_value = true;

	/* Lock before modifying! */
    pthread_mutex_lock (&mutex_connInfos);

	for(vector<ConnInfo*>::iterator it=connInfos->begin();
			it!=connInfos->end(); ++it)
	{
		if(packet.getPort() == (*it)->getPort() &&
				!strcmp(packet.getHostname(), (*it)->getHostName()))
		{
			return_value = false;
			break;
		}
	}

    /* Unlock after modifying! */
    pthread_mutex_unlock (&mutex_connInfos);

    return return_value;
}

void ServerMessageProcessor::process_conn_req(LSP_Packet& packet)
{
	fprintf(stderr, "ServerMessageProcessor:: Processing Connection Request from %s : %d\n",
			packet.getHostname(), packet.getPort());

	if(!check_conn_req_validity(packet))
	{
		fprintf(stderr, "ServerMessageProcessor:: Connection already exists! Ignoring request from %s : %d\n",
					packet.getHostname(), packet.getPort());
		return;
	}

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

	/* Need an empty packet to push in the connection ID
	 * Original packet will not have a connection ID set. It will have a 0 value
	 */
	LSP_Packet p(conn_id, 0, 0, NULL);
	LSP_Packet ack_packet = create_ack_packet(p);
	connInfo->add_to_outMsgs(ack_packet);
}

int ServerMessageProcessor::process_incoming_msg(LSP_Packet& packet)
{
	if(MessageProcessor::process_incoming_msg(packet) == FAILURE)
		return FAILURE;
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
	return SUCCESS;
}

int ServerMessageProcessor::process_data_packet(LSP_Packet& packet)
{
	switch(packet.getDataType())
	{
	case JOINREQUEST:
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
	return SUCCESS;
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
	string startS;
	iss >> startS;
	string endS;
	iss >> endS;
	int length = strlen(startS.c_str());
	unsigned workersCount = get_workers_count();
	if(workersCount == 0)
	{
		LSP_Packet c_pkt(create_not_found_packet(connInfo));
		connInfo->add_to_outMsgs(c_pkt);
		return;
	}
	if(length == 0)
	{
		LSP_Packet c_pkt(create_not_found_packet(connInfo));
		connInfo->add_to_outMsgs(c_pkt);
		return;
	}
	if(length>5)
	{
		LSP_Packet c_pkt(create_not_found_packet(connInfo));
		connInfo->add_to_outMsgs(c_pkt);
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
		int end = pow(26,length)-1;
		string startString = numToString(0,length);
        string endString = numToString(end,length);
	    string data = "c " + hash + " "+startString + " " +endString;
	    WorkerInfo w(cInfo->getConnectionId(), 0,0, end);
//		Send crack request to worker.
		send_crack_worker_request(packet, cInfo,w, data.c_str());
	}
	else if(length >= 4)
	{
		int start = 0;
		int numPoss = pow(26,length)-1;
		int each = ceil(numPoss/workersCount);
		for(vector<ConnInfo*>::iterator it=connInfos->begin();
								it!=connInfos->end(); ++it)
		{
			if((*it)->isIsAlive() && (*it)->isIsWorker())
			{
				ConnInfo* cInfo = (*it);
				int last;
				if(start+each>numPoss)
					last = 	numPoss;
				else
					last = 	start+each;
				string startString = numToString(start,length);
				string endString = numToString(last,length);
				string data = "c " + hash + " "  + startString + " " +endString;
				WorkerInfo w(cInfo->getConnectionId(), 0,start, last);
				send_crack_worker_request(packet, cInfo, w, data.c_str());
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
	conInfo->incrementSeqNo();
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
	vector<WorkerInfo> &workers = clientWorkerInfo[clientId];
	if(clientWorkerInfo.find(clientId) == clientWorkerInfo.end())
	{
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
		LSP_Packet c_pkt(create_not_found_packet(conInfo));
		conInfo->add_to_outMsgs(c_pkt);
//		Remove entry from map.
		assert(clientWorkerInfo.find(clientId)!=clientWorkerInfo.end());
		clientWorkerInfo.erase(clientId);
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

void ServerMessageProcessor::send_crack_worker_request(LSP_Packet &packet, ConnInfo* cInfo,WorkerInfo &w, const char* hash)
{
//	The crack request that the server sends to the worker will have the format
//	c hash lower upper
//	Add entry in map

	int connId = packet.getConnId();
	cInfo->incrementSeqNo();
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
	assert(clientWorkerInfo.find(connId)!=clientWorkerInfo.end());
//	Add connId of client to workers' clients queue.
	cInfo->pushClients(connId);
//	Send crack request to worker.
	fprintf(stderr, "ServerMessageProcessor:: Pushing crack packet to Outbox for conn_id: %u\n", cInfo->getConnectionId());
	LSP_Packet p(cInfo->getConnectionId(), cInfo->getSeqNo(),strlen(hash)+1, (uint8_t*)hash);
	cInfo->add_to_outMsgs(p);
}

ServerMessageProcessor::~ServerMessageProcessor()
{

}
