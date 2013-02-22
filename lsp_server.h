#pragma once
#ifndef LSP_SERVER_H
#define LSP_SERVER_H

#include "lsp.h"

class LSP_Server : public LSP
{
private:
	EpochServer* epoch;

public:
	LSP_Server(char* port);

	virtual void runEpoch();

	void init();
	void run();

	virtual ~LSP_Server();
};

typedef struct
{
	LSP_Server* server;
} lsp_server;

/* ---------------------------------------------------------------*/
/** lsp_server API FUNCTIONS */
/* ---------------------------------------------------------------*/
lsp_server* lsp_server_create(int port);
int  lsp_server_read(lsp_server* a_srv, void* pld, uint32_t* conn_id);
bool lsp_server_write(lsp_server* a_srv, void* pld, int lth, uint32_t conn_id);
bool lsp_server_close(lsp_server* a_srv, uint32_t conn_id);

#endif
