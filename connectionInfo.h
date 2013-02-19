#ifndef CONNECTIONINFO_H
#define CONNECTIONINFO_H

#include "lsppacket.h"

class ConnInfo : public Uncopyable
{
private:
	pthread_mutex_t mutex_outbox;
	queue<LSP_Packet> outMsgs;
	char hostName[INET_ADDRSTRLEN];
	int port;
	int connectionID;

	//might have to be made volatile
	unsigned epoch_count;

	/* Time stamp of the most recent communication that occured */
	clock_t timestamp;

//	int countMsgsRcd;

	/* Current sequence number with which a new message needs to be sent */
	int seq_no;

	bool isAlive;

	bool isWorker;
	bool processing; //false - processing, true - not processing

	/* Information to be stored only in case of request. */
	char* hash;
	int len;

	/* Information to be stored only in case of worker */
	queue<int> clients;

	bool msgSent;

public:
	/* Methods */
	ConnInfo(int connId, int p, const char* const host);

	void add_to_outMsgs(LSP_Packet packet);
	LSP_Packet get_front_msg() const;

	bool isMsgToBeSent() const;
	int getOutMsgsCount() const;
	void pop_outMsgs();
	int popClients();
	void pushClients(int client);
	int getConnectionId() const;
	void setConnectionId(int connectionId);
	char* getHash() const;
	void setHash(char* hash);
	const char* getHostName() const;
	bool isIsAlive() const;
	void setIsAlive(bool isAlive);
	bool isIsWorker() const;
	void setIsWorker(bool isWorker);
	int getLen() const;
	void setLen(int len);
	bool isMsgSent() const;
	void setMsgSent(bool msgSent);
	int getPort() const;
	void setPort(int port);
	int getSeqNo() const;
	void incrementSeqNo();

	void incrementEpochCount();
	void resetEpochCount();
	unsigned getEpochCount() const;

	clock_t getTimestamp() const;
	void updateTimestamp();

	~ConnInfo();
};

#endif

