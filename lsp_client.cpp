#include "lsp_client.h"
#include "serializer.h"
#include "connection.h"
#include "RequestMessageProcessor.h"
#include "WorkerMessageProcessor.h"
#include "epoch.h"

/* ---------------------------------------------------------------*/
/** lsp_client API FUNCTIONS */
/* ---------------------------------------------------------------*/
lsp_client* lsp_client_create(const char* src, int port)
{

}

int lsp_client_read(lsp_client* a_client, uint8_t* pld)
{


}

bool lsp_client_write(lsp_client* a_client, uint8_t* pld, int lth)
{

}

bool lsp_client_close(lsp_client* a_client)
{

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
