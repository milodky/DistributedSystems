/**
 * Header file for lsp protocol
 *
 */
#pragma once
#ifndef LSP_H
#define LSP_H

#include "header.h"


void lsp_set_epoch_lth(double lth);
void lsp_set_epoch_cnt(int cnt);
void lsp_set_drop_rate(double rate);

struct ThreadData
{
	LSP* lsp_instance;
};

class LSP : public Uncopyable
{
private:

protected:
	Inbox* inbox;
	MessageReceiver* msgReceiver;
	MessageSender* msgSender;
	Connector* connector;
	MessageProcessor* msg_proc;

	pthread_mutex_t mutex_connInfos;
	vector<ConnInfo*> *connInfos;

	char* serverPort;

	pthread_attr_t attr;

	/* This is the thread that will listen to all incoming activity. */
	pthread_t msg_recvr_thread;

	/* This is the thread that will keep checking if any msg has to be sent
	and send it */
	pthread_t msg_sender_thread;

	/* This is the epoch thread */
	pthread_t epoch_thread;

	void join_threads();

public:
	LSP(bool isServer,char* port);

	void init();

	void start_msg_receiver_thread();

	void start_msg_sender_thread();

	void start_epoch_thread();

	void runListener();

	void runTalker();

	virtual void runEpoch() = 0;

	virtual ~LSP();

	vector<ConnInfo*>* getConnInfos() const;
	pthread_mutex_t getMutexConnInfos() const;
};

class LSP_Server : public LSP
{
private:
	EpochServer* epoch;

public:
	LSP_Server(char* port);

	void create(int port);
	int  read(void* pld, uint32_t* conn_id);
	bool write(void* pld, int lth, uint32_t conn_id);
	// bool close(uint32_t conn_id);

	virtual void runEpoch();

	void init();
	void run();

	virtual ~LSP_Server();
};


class LSP_Client : public LSP
{
protected:
	char* host;
	EpochClient* epoch;

public:
	LSP_Client(char *h, char* port);

	void create(const char* dest, int port);

	int read(uint8_t* pld);
	bool write(uint8_t* pld, int lth);
	bool close();

	virtual void runEpoch();

	void init();
	void run();

	virtual ~LSP_Client();
};

class LSP_Worker : public LSP_Client
{
private:

public:
	void run();
	LSP_Worker(char *host, char* port);
	virtual ~LSP_Worker();

};

class LSP_Requester : public LSP_Client
{
private:
	char* hash;
	unsigned length;

public:
	void run();
	LSP_Requester(char* h, char* port, char* hashMsg, unsigned len);
	virtual ~LSP_Requester();
};

#endif
