#include "epoch.h"
#include "lsp.h"

Epoch::Epoch(LSP* lsp) :lsp(lsp)
{

}

Epoch::~Epoch()
{

}
/* ---------------------------------------------------------------*/
/** EpochServer METHODS */
/* ---------------------------------------------------------------*/
EpochServer::EpochServer(LSP* lsp) : Epoch(lsp)
{

}

LSP_Server* EpochServer::get_lsp()
{
	return (LSP_Server*) lsp;
}

EpochServer::~EpochServer()
{

}
/* ---------------------------------------------------------------*/
/** EpochClient METHODS */
/* ---------------------------------------------------------------*/
EpochClient::EpochClient(LSP* lsp) : Epoch(lsp)
{

}

LSP_Client* EpochClient::get_lsp()
{
	return (LSP_Client*) lsp;
}

EpochClient::~EpochClient()
{

}
