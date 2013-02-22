#include <signal.h>

#include "lsp.h"
#include "serializer.h"
#include "connectionInfo.h"
#include "inbox.h"
#include "connection.h"
#include "MessageReceiver.h"
#include "MessageSender.h"
#include "ServerMessageProcessor.h"
#include "RequestMessageProcessor.h"
#include "WorkerMessageProcessor.h"
#include "epoch.h"

double epoch_lth = _EPOCH_LTH;
int epoch_cnt = _EPOCH_CNT;
double drop_rate = _DROP_RATE;

bool destroy_thread = false;

/** LSP RELATED FUNCTIONS */

void lsp_set_epoch_lth(double lth){epoch_lth = lth;}
void lsp_set_epoch_cnt(int cnt){epoch_cnt = cnt;}
void lsp_set_drop_rate(double rate){drop_rate = rate;}

/** LSP Methods */

/* ---------------------------------------------------------------*/
/** THREAD FUNCTION CALLS */
/* ---------------------------------------------------------------*/
void* listener_run(void* arg)
{
	struct ThreadData* params = (ThreadData *) arg;
	fprintf(stderr, "LSP:: Running Listener Thread...\n");
	params->lsp_instance->runListener();
	delete params;
}

void* talker_run(void* arg)
{
	struct ThreadData* params = (ThreadData *) arg;
	fprintf(stderr, "LSP:: Running Talker Thread...\n");
	params->lsp_instance->runTalker();
	delete params;
}

void* epoch_run(void* arg)
{
	struct ThreadData* params = (ThreadData *) arg;
	fprintf(stderr, "LSP:: Running Epoch Thread...\n");
	params->lsp_instance->runEpoch();
	delete params;
}

/* ---------------------------------------------------------------*/
/** LSP METHODS */
/* ---------------------------------------------------------------*/
LSP::LSP(bool isServer, char* port)
{
	serverPort = port;

	inbox = new Inbox();
	connInfos = new vector<ConnInfo*>();
	connector = new Connector(isServer);
	msgReceiver = new MessageReceiver(inbox);

	pthread_mutex_init(&mutex_connInfos, NULL);
	msgSender = new MessageSender(connInfos, mutex_connInfos, connector);
	/* Binding the socket connector and msg receiver class */
	connector->setMsgReceiver(msgReceiver);
}

void LSP::init()
{
	if (pthread_attr_init(&attr))
	{
		perror("pthread_attr_init");
		exit(FAILURE);
	}
}

void LSP::start_msg_receiver_thread()
{
	int e;
	ThreadData *data = new ThreadData();
	data->lsp_instance = this;

	if (e = pthread_create(&msg_recvr_thread, &attr, listener_run, (void *) data))
		Error("pthread_create %d", e);
}

void LSP::start_msg_sender_thread()
{
	int e;
	ThreadData* data = new ThreadData();
	data->lsp_instance = this;

	if (e = pthread_create(&msg_sender_thread, &attr, talker_run, (void *) data))
		Error("pthread_create %d", e);
}

void LSP::start_epoch_thread()
{
	int e;
	ThreadData* data = new ThreadData();
	data->lsp_instance = this;

	if (e = pthread_create(&epoch_thread, &attr, epoch_run, (void *) data))
		Error("pthread_create %d", e);
}

void LSP::runListener()
{
	connector->listen();
}

void LSP::runTalker()
{
	assert(msgSender != NULL);
	msgSender->pollToSend(connInfos);
}

void LSP::join_threads()
{
	if (pthread_join(msg_recvr_thread, NULL))
		Error("pthread_join");
	fprintf(stderr, "Joined Listener Thread.\n");

	if (pthread_join(msg_sender_thread, NULL))
			Error("pthread_join");
	fprintf(stderr, "Joined Sender Thread.\n");

	if (pthread_join(epoch_thread, NULL))
		Error("pthread_join");
	fprintf(stderr, "Joined Epoch Thread.\n");
}

LSP::~LSP()
{
	pthread_kill(msg_recvr_thread, SIGINT);
	destroy_thread = true;
	join_threads();

	if(connector) delete connector;
	if(msgReceiver) delete msgReceiver;
	if(inbox) delete inbox;
	if(msgSender) delete msgSender;

	if(connInfos)
	{
		/* Lock before modifying! */
		pthread_mutex_lock (&mutex_connInfos);

		for(vector<ConnInfo*>::iterator it=connInfos->begin(); it!=connInfos->end(); ++it)
		{
			if((*it)) delete (*it);
		}

		/* Unlock after modifying! */
		pthread_mutex_unlock (&mutex_connInfos);

		delete connInfos;
	}

	pthread_mutex_destroy(&mutex_connInfos);
}

vector<ConnInfo*>* LSP::getConnInfos() {
	return connInfos;
}

pthread_mutex_t& LSP::getMutexConnInfos() {
	return mutex_connInfos;
}

MessageProcessor* LSP::getMsgProc() const {
	return msg_proc;
}

MessageReceiver* LSP::getMsgReceiver() const {
	return msgReceiver;
}

MessageSender* LSP::getMsgSender() const {
	return msgSender;
}
