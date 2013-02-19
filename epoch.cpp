#include <pthread.h>
#include <time.h>

#include "epoch.h"
#include "lsp.h"
#include "connectionInfo.h"
#include "ServerMessageProcessor.h"
#include "RequestMessageProcessor.h"
#include "WorkerMessageProcessor.h"

Epoch::Epoch(LSP* lsp) :lsp(lsp)
{

}

void Epoch::run()
{

}

bool Epoch::epoch_passed(const clock_t start, const clock_t end)
{
	return (end - start) / CLOCKS_PER_SEC >= _EPOCH_LTH;
}

int Epoch::check_epoch(ConnInfo* connInfo)
{
	clock_t last, current;

	/* Get the last time stamp marked on the connInfo */
	last = connInfo->getTimestamp();

	/* Get the current clock */
	current = clock();

	/* Connection has been broken. */
	if (connInfo->getEpochCount() >= _EPOCH_CNT)
	{
		return FAILURE;
	}

	/* Epoch passed. Epoch count yet to reach _EPOCH_CNT */
	if (epoch_passed(last, current))
	{
		if(connInfo->getEpochCount() > 0)
			fprintf(stderr, "EpochClient:: Conn_id: %d EPOCH PASSED. count: %u\n",
					connInfo->getConnectionId(), connInfo->getEpochCount());
		connInfo->updateTimestamp();
		connInfo->incrementEpochCount();
		take_action(connInfo);
	}

	return SUCCESS;
}

void Epoch::send_packet_again(ConnInfo* connInfo)
{
	assert (connInfo->getOutMsgsCount() != 0);

	LSP_Packet packet = connInfo->get_front_msg();
//	fprintf(stderr, "Epoch:: Packet marked for re-send.\n");
//	packet.print();

	/* Setting the message sent to false enables
	 * the message sender to pop off the msg from the outbox */
	connInfo->setMsgSent(false);
}

Epoch::~Epoch()
{

}
/* ---------------------------------------------------------------*/
/** EpochServer METHODS */
/* ---------------------------------------------------------------*/
EpochServer::EpochServer(LSP* lsp) : Epoch(lsp)
{
	connInfos = NULL;
}

LSP_Server* EpochServer::get_lsp()
{
	return (LSP_Server*) lsp;
}

void EpochServer::run()
{
	vector<ConnInfo*>* connInfos = get_lsp()->getConnInfos();
	pthread_mutex_t& mutex_connInfos = get_lsp()->getMutexConnInfos();

	while(true)
	{
		/* Lock before modifying! */
		pthread_mutex_lock (&mutex_connInfos);

		vector<ConnInfo*>::iterator it=connInfos->begin();
		while(it!=connInfos->end())
		{
			/* *it refers to the vector element which is ConnInfo* */
			if(check_epoch(*it) == FAILURE)
			{
				/* Client did not respond within the epoch count */
				fprintf(stderr, "\nEpoch:: CONNECTION EXPIRED for Client conn_id: %d\n",
						(*it)->getConnectionId());
				delete *it;
				connInfos->erase(it);
			}
			else
			{
				++it;
			}
		}

		/* Unlock after modifying! */
		pthread_mutex_unlock (&mutex_connInfos);

		sleep(0);
	}
}

int EpochServer::take_action(ConnInfo* connInfo)
{
	if((connInfo->getOutMsgsCount() != 0))
	{
		send_packet_again(connInfo);
	}
	else
	{
		/**
		 * Send an acknowledgment message with sequence number 0
		 * if no data messages have been received i.e. when no ACK message
		 * is present in the outbox
		 */
		LSP_Packet ack_packet(connInfo->getConnectionId(), 0, 0, NULL);
		connInfo->add_to_outMsgs(ack_packet);
		send_packet_again(connInfo);
	}
	return 0;
}

EpochServer::~EpochServer()
{

}
/* ---------------------------------------------------------------*/
/** EpochClient METHODS */
/* ---------------------------------------------------------------*/
EpochClient::EpochClient(LSP* lsp) : Epoch(lsp)
{
	connInfo = NULL;
}

LSP_Client* EpochClient::get_lsp()
{
	return (LSP_Client*) lsp;
}

void EpochClient::run()
{
	vector<ConnInfo*>* const connInfos = get_lsp()->getConnInfos();
	while(connInfos->size() != 1);

	connInfo = get_lsp()->getConnInfos()->at(0);

	clock_t last, current;
	while(true)
	{
		if(check_epoch(connInfo) == FAILURE)
		{
			/* Server did not respond in time. Exiting.. */
			fprintf(stderr, "EpochClient:: Conn_id: %d EPOCH COUNT REACHED MAX. count: %u\n",
							connInfo->getConnectionId(), connInfo->getEpochCount());
			fprintf(stderr, "Connection terminated with Server. Exiting...\n");
			exit (FAILURE);
		}
		sleep(0);
	}
}


int EpochClient::take_action(ConnInfo* connInfo)
{
	if((connInfo->getOutMsgsCount() != 0))
	{
		send_packet_again(connInfo);
	}
	else
	{
		/**
		 * Send an acknowledgment message with sequence number 0
		 * if no data messages have been received i.e. when no ACK message
		 * is present in the outbox
		 */
		LSP_Packet ack_packet(connInfo->getConnectionId(), 0, 0, NULL);
		connInfo->add_to_outMsgs(ack_packet);
		send_packet_again(connInfo);
	}
	return 0;
}

EpochClient::~EpochClient()
{

}
