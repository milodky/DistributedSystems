#include <pthread.h>

#include "epoch.h"
#include "lsp.h"
#include "connectionInfo.h"


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

}

int EpochServer::take_action()
{

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
		last = connInfo->getTimestamp();
		current = clock();

		if(epoch_passed(last, current))
		{
			fprintf(stderr, "EpochClient:: EPOCH PASSED. count: %u\n", connInfo->getEpochCount());
			connInfo->updateTimestamp();
			connInfo->incrementEpochCount();
			take_action();
		}
	}
}
int EpochClient::take_action()
{
	assert (connInfo != NULL);


}

EpochClient::~EpochClient()
{

}
