#include "lsp.h"
// #include "lspmessage.pb-c.h"

double epoch_lth = _EPOCH_LTH;
int epoch_cnt = _EPOCH_CNT;
double drop_rate = _DROP_RATE;

/*
 *
 *
 *				LSP RELATED FUNCTIONS
 *
 *
 */

void lsp_set_epoch_lth(double lth){epoch_lth = lth;}
void lsp_set_epoch_cnt(int cnt){epoch_cnt = cnt;}
void lsp_set_drop_rate(double rate){drop_rate = rate;}

/** LSP Methods */

/**
 * Code for execution as the listener thread
 */
void* listener_run(void* arg)
{
	struct ListenerData* params = (struct ListenerData *) arg;
	printf("Running Listener Thread...\n");
	params->lsp_instance->runListener();
}

/* LSP CLASS METHODS */
LSP::LSP(bool isServer)
{
	inbox = new Inbox();
	connector = new Connector(isServer);
	msgReceiver = new MessageReceiver(inbox);
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
	ListenerData listener_data = {this};
	if (e = pthread_create(&msg_recvr_thread, &attr, listener_run,
							(void *) &listener_data))
		Error("pthread_create %d", e);
}

void LSP::runListener()
{
	connector->listen();
}

LSP::~LSP()
{
	if (pthread_join(msg_recvr_thread, NULL))
		Error("pthread_join");
	printf("Joined Listener Thread.\n");

	if(connector) delete connector;
	if(msgReceiver) delete msgReceiver;
	if(inbox) delete inbox;
}

/** LSP_Server METHODS */
void LSP_Server::init()
{
	LSP::init();
	connector->setup(NULL, SERVER_PORT);
	start_msg_receiver_thread();
//		connector.send_message("test");
}

/** LSP_Client METHODS */
void LSP_Client::init()
{
	LSP::init();
	connector->setup(LOCALHOST, SERVER_PORT);
//		connector.send_message("test");
}
