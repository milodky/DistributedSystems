/**
 * Header file for lsp protocol
 *
 */
#pragma once
#ifndef LSP_H
#define LSP_H

#include "header.h"

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

	vector<ConnInfo*>* getConnInfos();
	pthread_mutex_t& getMutexConnInfos();
	MessageProcessor* getMsgProc() const;
	MessageReceiver* getMsgReceiver() const;
	MessageSender* getMsgSender() const;
};

#endif
