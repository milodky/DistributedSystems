#include "epoch.h"

Epoch::Epoch(LSP* lsp) :lsp(lsp)
{

}

/* ---------------------------------------------------------------*/
/** EpochServer METHODS */
/* ---------------------------------------------------------------*/
LSP_Server* EpochServer::get_lsp()
{
	return (LSP_Server*) lsp;
}

/* ---------------------------------------------------------------*/
/** EpochClient METHODS */
/* ---------------------------------------------------------------*/

LSP_Client* EpochClient::get_lsp()
{
	return (LSP_Client*) lsp;
}
