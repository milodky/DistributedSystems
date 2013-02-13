#ifndef CONNECTIONINFO_H
#define CONNECTIONINFO_H

#include "lsppacket.h"
#include "lsp.h"
#include "header.h"
#include "connection.h"

class ConnInfo : public Uncopyable
{
private:

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


	queue<LSP_Packet> outMsgs;

	/* Methods */
	ConnInfo(int connId, int p, const char* const host);

	void add_to_outMsgs(LSP_Packet packet);

	bool isMsgToBeSent();
	int getOutMsgsCount() const;
};

#endif

