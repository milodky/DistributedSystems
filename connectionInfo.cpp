#include "connectionInfo.h"

ConnInfo::ConnInfo(int connId, int p, const char* const host) : connectionID(connId), port(p)
{
	/* Copy Hostname */
	strcpy(this->hostName, host);

	//default values when constructed.
	msgSent = false; //Only now connection request has come in. So msgSent will be false.
	isAlive = true;  //Assumed alive since connection request has just come in.
	isWorker = false;
	//change these based on client and server
	//	countMsgsRcd = 1; //only connection request is got at this point.

	seq_no = 0;
	epochsSinceMsgRcd = 0;
	epochsSinceMsgSent = 0;

	pthread_mutex_init(&mutex_outbox, NULL);
}

void ConnInfo::add_to_outMsgs(LSP_Packet packet)
{
	/* Lock before modifying! */
	pthread_mutex_lock (&mutex_outbox);

	fprintf(stderr, "ConnInfo::Adding packet to conn_id:%d Outbox:\n", connectionID);
	outMsgs.push(packet);

	/* Unlock after modifying! */
	pthread_mutex_unlock (&mutex_outbox);
}

LSP_Packet ConnInfo::get_front_msg() const
{
	return outMsgs.front();
}

void ConnInfo::pop_outMsgs()
{
	/* Lock before modifying! */
	pthread_mutex_lock (&mutex_outbox);

	fprintf(stderr, "ConnInfo::Popping packet to conn_id:%d Outbox:\n", connectionID);
	outMsgs.pop();

	/* Unlock after modifying! */
	pthread_mutex_unlock (&mutex_outbox);
}

bool ConnInfo::isMsgToBeSent() const
{
	if(isAlive && !msgSent && outMsgs.size()!=0)
		return true;
	return false;
}

int ConnInfo::getOutMsgsCount() const
{
	return outMsgs.size();
}

void ConnInfo::setWorker(bool worker)
{
	isWorker = worker;
}

ConnInfo::~ConnInfo()
{
	pthread_mutex_destroy(&mutex_outbox);
}
