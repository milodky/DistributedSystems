#include "lsp_server.h"
#include "connection.h"
#include "ServerMessageProcessor.h"
#include "epoch.h"

/* ---------------------------------------------------------------*/
/** lsp_server API FUNCTIONS */
/* ---------------------------------------------------------------*/
lsp_server* lsp_server_create(int port)
{

}

int lsp_server_read(lsp_server* a_srv, void* pld, uint32_t* conn_id)
{

}

bool lsp_server_write(lsp_server* a_srv, void* pld, int lth, uint32_t conn_id)
{

}

bool lsp_server_close(lsp_server* a_srv, uint32_t conn_id)
{

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
