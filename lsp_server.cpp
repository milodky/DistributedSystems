#include "lsp_server.h"
#include "connection.h"
#include "ServerMessageProcessor.h"
#include "MessageSender.h"
#include "epoch.h"
#include "inbox.h"
#include "lsppacket.h"
#include "connectionInfo.h"

/* ---------------------------------------------------------------*/
/** lsp_server API FUNCTIONS */
/* ---------------------------------------------------------------*/
lsp_server* lsp_server_create(int port)
{
	lsp_server* a_srv = (lsp_server*) malloc (sizeof(lsp_server));
	if (a_srv == NULL) exit (FAILURE);

	char port_s[10];
	sprintf(port_s, "%d", port);
	a_srv->server = new LSP_Server(port_s);
	a_srv->server->init();

	MessageProcessor* msg_proc = a_srv->server->getMsgProc();
	msg_proc->testing = true;

	return a_srv;
}

int lsp_server_read(lsp_server* a_srv, void* pld, uint32_t* conn_id)
{
	MessageProcessor* msg_proc = a_srv->server->getMsgProc();

	Inbox* inbox = msg_proc->getInbox();
	if(!inbox->isEmpty())
	{
		LSP_Packet packet = inbox->pop_msg();

		msg_proc->process_incoming_msg(packet);

		if(packet.getLen() != 0)
		{
			*conn_id = packet.getConnId();
			pld = packet.getBytes();

			return packet.getLen();
		}
	}
	return NULL;
}

bool lsp_server_write(lsp_server* a_srv, void* pld, int lth, uint32_t conn_id)
{
	if(lth == 0 || pld == NULL) return 0;

	MessageSender* msgSender = a_srv->server->getMsgSender();
	MessageProcessor* msg_proc = a_srv->server->getMsgProc();

	ConnInfo* connInfo = msg_proc->get_conn_info(conn_id);

	if(connInfo != NULL)
	{
		connInfo->incrementSeqNo();
		LSP_Packet packet(conn_id, connInfo->getSeqNo(), lth, (uint8_t*) pld);
		connInfo->add_to_outMsgs(packet);
	}
	return true;
}

bool lsp_server_close(lsp_server* a_srv, uint32_t conn_id)
{
	MessageProcessor* msg_proc = a_srv->server->getMsgProc();
	ConnInfo* connInfo = msg_proc->get_conn_info(conn_id);

	vector<ConnInfo*> *connInfos = a_srv->server->getConnInfos();

	for(vector<ConnInfo*>::iterator it = connInfos->begin();
			it!=connInfos->end(); ++it)
	{
		if((*it)->getConnectionId() == conn_id)
		{
			delete *it;
			connInfos->erase(it);
			return true;
		}
	}

	return false;
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
