/**
 * Header file for lsp protocol
 *
 */

#ifndef LSP_H
#define LSP_H

#include "header.h"
#include "MessageReceiver.h"
#include "MessageSender.h"
#include "connection.h"
#include "connectionInfo.h"
#include "inbox.h"

// Global Parameters. For both server and clients.

#define _EPOCH_LTH 2.0
#define _EPOCH_CNT 5;
#define _DROP_RATE 0.0;

void lsp_set_epoch_lth(double lth);
void lsp_set_epoch_cnt(int cnt);
void lsp_set_drop_rate(double rate);

/* Inbox Thread */

/* Outbox Thread */
void* listener_run(void*);

struct ListenerData
{
	LSP* lsp_instance;
};

struct TalkerData
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
	vector<ConnInfo*> *connectionInfo;


	pthread_attr_t attr;
	/* This is the thread that will listen to all incoming activity. */
	pthread_t msg_recvr_thread;
	/* This is the thread that will keep checking if any msg has to be sent
	and send it*/
	pthread_t msg_sender_thread;

public:
	LSP(bool isServer);

	void init();

	void start_msg_receiver_thread();

	void start_msg_sender_thread();

	void runListener();

	void runTalker();

	virtual ~LSP();
};

class LSP_Server : public LSP
{
private:

public:
	LSP_Server() : LSP(true) {}

	void create(int port);
	int  read(void* pld, uint32_t* conn_id);
	bool write(void* pld, int lth, uint32_t conn_id);
	// bool close(uint32_t conn_id);

	void init();

	virtual ~LSP_Server()
	{

	}
};


class LSP_Client : public LSP
{
public:
	LSP_Client() : LSP(false) {}
	void create(const char* dest, int port);

	int read(uint8_t* pld);
	bool write(uint8_t* pld, int lth);
	bool close();

	void init();

	virtual ~LSP_Client()
	{

	}
};

class LSP_Worker : public LSP_Client
{

};

class LSP_Requester : public LSP_Client
{

};

#endif
