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

	void create(int port);
	int  read(void* pld, uint32_t* conn_id);
	bool write(void* pld, int lth, uint32_t conn_id);
	// bool close(uint32_t conn_id);

	virtual void runEpoch();

	void init();
	void run();

	virtual ~LSP_Server();
};


#endif
