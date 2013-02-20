#pragma once
#ifndef LSP_CLIENT_H
#define LSP_CLIENT_H

#include "lsp.h"

class LSP_Client : public LSP
{
protected:
	char* host;
	EpochClient* epoch;

public:
	LSP_Client(char *h, char* port);

	void create(const char* dest, int port);

	int read(uint8_t* pld);
	bool write(uint8_t* pld, int lth);
	bool close();

	virtual void runEpoch();

	void init();
	void run();

	virtual ~LSP_Client();
};

class LSP_Worker : public LSP_Client
{
private:

public:
	void run();
	LSP_Worker(char *host, char* port);
	virtual ~LSP_Worker();

};

class LSP_Requester : public LSP_Client
{
private:
	char* hash;
	unsigned length;

public:
	void run();
	LSP_Requester(char* h, char* port, char* hashMsg, unsigned len);
	virtual ~LSP_Requester();
};

#endif
