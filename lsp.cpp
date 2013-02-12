#include "lsp.h"
#include "serializer.h"
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
	delete params;
}

void* talker_run(void* arg)
{
	struct TalkerData* params = (struct TalkerData *) arg;
	printf("Running Talker Thread...\n");
	params->lsp_instance->runTalker();
	delete params;
}


/* LSP CLASS METHODS */
LSP::LSP(bool isServer,char* port)
{
	serverPort = port;
	inbox = new Inbox();
	connectionInfo = new vector<ConnInfo*>();
	connector = new Connector(isServer);
	msgReceiver = new MessageReceiver(inbox);
	msgSender = new MessageSender(connectionInfo,connector);
	/* Binding the socket connector and msg receiver class */
	connector->setMsgReceiver(msgReceiver);
}

void LSP::init()
{
//	//Test-sanu - remove later
//	ConnInfo *c = new ConnInfo(0,1,"C1");
//	LSP_Packet p(0,1,strlen("Hello"),(uint8_t*)"Hello");
//	c->outMsgs.push(p);
//	connectionInfo->push_back(c);


	if (pthread_attr_init(&attr))
	{
		perror("pthread_attr_init");
		exit(FAILURE);
	}
}

void LSP::start_msg_receiver_thread()
{
	int e;
	ListenerData *listener_data = new ListenerData();
	listener_data->lsp_instance = this;

	if (e = pthread_create(&msg_recvr_thread, &attr, listener_run,
							(void *) listener_data))
		Error("pthread_create %d", e);
}

void LSP::start_msg_sender_thread()
{
	int e;
	TalkerData* talker_data = new TalkerData();
	talker_data->lsp_instance = this;

	if (e = pthread_create(&msg_sender_thread, &attr, talker_run,
							(void *) talker_data))
		Error("pthread_create %d", e);
}

void LSP::runListener()
{
	connector->listen();
}

void LSP::runTalker()
{
	assert(msgSender != NULL);
	msgSender->pollToSend(connectionInfo);
}

LSP::~LSP()
{
	if (pthread_join(msg_recvr_thread, NULL))
		Error("pthread_join");
	if (pthread_join(msg_sender_thread, NULL))
			Error("pthread_join");
	printf("Joined Listener Thread.\n");
	printf("Joined Sender Thread.\n");

	if(connector) delete connector;
	if(msgReceiver) delete msgReceiver;
	if(inbox) delete inbox;
	if(msgSender) delete msgSender;
	if(connectionInfo) delete connectionInfo;

}

/** LSP_Server METHODS */
void LSP_Server::init()
{
	LSP::init();
	connector->setup(NULL, SERVER_PORT);
	start_msg_receiver_thread();
	// connector->send_message((uint8_t*) "test", 6);
	start_msg_sender_thread();

//		connector.send_message("test");
}

/** LSP_Client METHODS */
void LSP_Client::init()
{
	LSP::init();
	connector->setup(LOCALHOST, SERVER_PORT);
	start_msg_receiver_thread();
	uint8_t *bytes;
	uint8_t *text = (uint8_t*) "text!\0";

	LSP_Packet packet(40, 50, strlen( (char*)text), text);
	packet.print();

	Serializer s;
	int len = s.marshal(packet, bytes);
	fprintf(stderr,"Writing %d serialized bytes\n", len); // See the length of message
	fwrite (bytes, len, 1, stdout);           // Write to stdout to allow direct command line piping
	printf("\n");

	connector->send_message(bytes, len);
}
