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

/*
 *				LSP RELATED FUNCTIONS
 */

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

/* ---------------------------------------------------------------*/
/** LSP_Server METHODS */
/* ---------------------------------------------------------------*/
LSP_Server::LSP_Server(char* port) : LSP(true,port)
{
	msg_proc = new ServerMessageProcessor(inbox, connInfos, mutex_connInfos);
	epoch = new EpochServer(this);
}

void LSP_Server::runEpoch()
{
	epoch->run();
}

void LSP_Server::init()
{
	LSP::init();
	if (connector->setup(NULL, serverPort) == 2)
	{
		Error("LSP_Server::Exception in Connection. Exiting Server.");
	}

	start_msg_receiver_thread();
	start_msg_sender_thread();
	start_epoch_thread();
}

void LSP_Server::run()
{
	msg_proc->poll_inbox();
}

LSP_Server::~LSP_Server()
{
	if (msg_proc) delete msg_proc;
	if (epoch) delete epoch;
}
/* ---------------------------------------------------------------*/
/** LSP_Client METHODS */
/* ---------------------------------------------------------------*/
LSP_Client::LSP_Client(char *h, char* port) : LSP(false,port),host(h)
{
	epoch = new EpochClient(this);
}

void LSP_Client::runEpoch()
{
	epoch->run();
}

void LSP_Client::init()
{
	LSP::init();
	connector->setup(host, serverPort);
	start_msg_receiver_thread();
	start_msg_sender_thread();
	start_epoch_thread();
}

void LSP_Client::run()
{
	msg_proc->send_conn_req_packet(host, serverPort);
	if(msg_proc->poll_inbox() == COMPLETE)
	{
		printf("Exiting!\n");
		//TODO: change this
		exit(0);
	}
}

LSP_Client::~LSP_Client()
{
	if (epoch) delete epoch;
}

/* ---------------------------------------------------------------*/
/** LSP_Worker METHODS */
/* ---------------------------------------------------------------*/
LSP_Worker::LSP_Worker(char *host, char* port) : LSP_Client(host,port)
{
	msg_proc = new WorkerMessageProcessor(inbox, connInfos, mutex_connInfos);
}

void LSP_Worker::run()
{
	LSP_Client::run();
}

LSP_Worker::~LSP_Worker()
{
	if (msg_proc) delete msg_proc;
}

/* ---------------------------------------------------------------*/
/** LSP_Requester METHODS */
/* ---------------------------------------------------------------*/
LSP_Requester::LSP_Requester(char* h, char* port, char* hashMsg, unsigned len):
	LSP_Client(h,port),hash(hashMsg),length(len)
{
	msg_proc = new RequestMessageProcessor(inbox, connInfos, mutex_connInfos);
}

void LSP_Requester::run()
{
	((RequestMessageProcessor*) msg_proc)->set_password_data(hash, length);
	LSP_Client::run();
}

LSP_Requester::~LSP_Requester()
{
	if (msg_proc) delete msg_proc;
}
