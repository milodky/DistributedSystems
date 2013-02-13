#ifndef CONNECTIONINFO_H
#define CONNECTIONINFO_H

#include "lsppacket.h"

class ConnInfo : public Uncopyable
{
private:
	pthread_mutex_t mutex_outbox;
	queue<LSP_Packet> outMsgs;

public:
	char hostName[INET_ADDRSTRLEN];
	int port;
	int connectionID;

	//might have to be made volatile
	int epochsSinceMsgRcd;
	int epochsSinceMsgSent;

//	int countMsgsRcd;

	/* Current sequence number with which a new message needs to be sent */
	int seq_no;

	bool isAlive;
	bool isWorker;

	bool msgSent;

	/* Methods */
	ConnInfo(int connId, int p, const char* const host);

	/* OutBox Handling */
	void add_to_outMsgs(LSP_Packet packet);
	LSP_Packet get_front_msg() const;
	void pop_outMsgs();

	bool isMsgToBeSent() const;
	int getOutMsgsCount() const;
	void setWorker(bool worker);
	~ConnInfo();

};

#endif

