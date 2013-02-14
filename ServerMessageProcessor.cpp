#include "ServerMessageProcessor.h"

ServerMessageProcessor::ServerMessageProcessor(Inbox* in, vector<ConnInfo*> *infos)
	: MessageProcessor(in,infos)
{

}

void ServerMessageProcessor::process_conn_req(LSP_Packet& packet)
{
	fprintf(stderr, "ServerMessageProcessor:: Processing Connection Request from %s : %d\n", packet.getHostname(), packet.getPort());
	/* Create a new connection info object for this client */
	unsigned conn_id = get_next_conn_id();
	ConnInfo *connInfo =
			new ConnInfo(conn_id, packet.getPort(), packet.getHostname());

	connInfos->push_back(connInfo);

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
//	crack request to server comes from request and is of the format
//	c sha len
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
			if((*it)->isAlive && (*it)->isWorker)
			{
				cInfo = (*it);
				break;
			}
		}
		std::ostringstream sin;
        sin << 	pow(26,length);
        string end = sin.str();
	    string data = "c " + hash + " 0" + "  " +end;
//	    Add entry in map
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
			if((*it)->isAlive && (*it)->isWorker)
			{
				ConnInfo* cInfo = (*it);
				std::ostringstream sin;
				sin << start;
				string startString = sin.str();
				if(start+each>numPoss)
					sin << 	numPoss;
				else
					sin << 	start+each;
				string endString = sin.str();
				string data = "c " + hash + " "  + startString + "  " +endString;
//	    Add entry in map
				send_crack_worker_request(cInfo, data.c_str());
				start = start + each + 1;
			}
		}
	}
}


void ServerMessageProcessor::process_join_request_packet(LSP_Packet& packet)
{
	ConnInfo* cInfo = get_conn_info(packet.getConnId());
	cInfo->setWorker(true);
}


void ServerMessageProcessor::process_found_packet(LSP_Packet& packet)
{
//	Update map entry. Send result to client. Remove map entry.
	ConnInfo* cInfo = get_conn_info(packet.getConnId());
	cInfo->setWorker(true);
}

void ServerMessageProcessor::process_not_found_packet(LSP_Packet& packet)
{
//	Update map entry. If all have returned 'not found', send message to client,
//	remove map entry.
	ConnInfo* cInfo = get_conn_info(packet.getConnId());
	cInfo->setWorker(true);
}


unsigned ServerMessageProcessor::get_workers_count()
{
	unsigned count =0;
	for(vector<ConnInfo*>::iterator it=connInfos->begin();
					it!=connInfos->end(); ++it)
	{
		if((*it)->isAlive && (*it)->isWorker)
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
	LSP_Packet packet(cInfo->connectionID, cInfo->seq_no,strlen(hash), (uint8_t*)hash);
	cInfo->add_to_outMsgs(packet);
}

ServerMessageProcessor::~ServerMessageProcessor()
{

}
