#include "lsp_client.h"
#include "serializer.h"
#include "connection.h"
#include "RequestMessageProcessor.h"
#include "WorkerMessageProcessor.h"
#include "epoch.h"
#include "connection.h"
#include "MessageSender.h"
#include "inbox.h"
#include "lsppacket.h"
#include "connectionInfo.h"

/* ---------------------------------------------------------------*/
/** lsp_client API FUNCTIONS */
/* ---------------------------------------------------------------*/
lsp_client* lsp_client_create(const char* src, int port)
{
	lsp_client* a_client = (lsp_client*) malloc (sizeof(lsp_client));
	if (a_client == NULL) exit (FAILURE);

	char port_s[10];
	sprintf(port_s, "%d", port);
	a_client->client = new LSP_Worker(const_cast<char*>(src), port_s);
	a_client->client->init();

	MessageProcessor* msg_proc = a_client->client->getMsgProc();
	msg_proc->testing = true;
	a_client->client->send_conn_req();

	return a_client;
}

int lsp_client_read(lsp_client* a_client, uint8_t* pld)
{
	MessageProcessor* msg_proc = a_client->client->getMsgProc();

	Inbox* inbox = msg_proc->getInbox();
	if(!inbox->isEmpty())
	{
		LSP_Packet packet = inbox->pop_msg();

		msg_proc->process_incoming_msg(packet);

		if(packet.getLen() != 0)
		{
			memcpy(pld, packet.getBytes(), packet.getLen());

			return packet.getLen();
		}
	}
	return NULL;
}

bool lsp_client_write(lsp_client* a_client, uint8_t* pld, int lth)
{
	if(lth == 0 || pld == NULL) return 0;

	MessageSender* msgSender = a_client->client->getMsgSender();
	MessageProcessor* msg_proc = a_client->client->getMsgProc();

	vector<ConnInfo*> *connInfos = a_client->client->getConnInfos();

	for(vector<ConnInfo*>::iterator it = connInfos->begin();
			it!=connInfos->end(); ++it)
	{
		ConnInfo* connInfo = *it;
		connInfo->incrementSeqNo();
		LSP_Packet packet(connInfo->getConnectionId(), connInfo->getSeqNo(), lth, (uint8_t*) pld);
		connInfo->add_to_outMsgs(packet);

		break;
	}

	return true;
}

bool lsp_client_close(lsp_client* a_client)
{
	MessageProcessor* msg_proc = a_client->client->getMsgProc();
	vector<ConnInfo*> *connInfos = a_client->client->getConnInfos();

	for(vector<ConnInfo*>::iterator it = connInfos->begin();
			it!=connInfos->end(); ++it)
	{
		delete *it;
		connInfos->erase(it);
		return true;
	}

	return false;
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
	if(connector->setup(host, serverPort) == 2)
		Error("LSP_Client::Exception in Connection. Exiting...");
	start_msg_receiver_thread();
	start_msg_sender_thread();
	start_epoch_thread();
}


void LSP_Client::send_conn_req()
{
	msg_proc->send_conn_req_packet(host, serverPort);
}

void LSP_Client::run()
{
	msg_proc->send_conn_req_packet(host, serverPort);
	if(msg_proc->poll_inbox() == COMPLETE)
	{
		printf("Disconnected\n");
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
