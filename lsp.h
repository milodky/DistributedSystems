/**
 * Header file for lsp protocol
 *
 */

#ifndef LSP_H
#define LSP_H

#include "header.h"
#include "connection.h"

// Global Parameters. For both server and clients.

#define _EPOCH_LTH 2.0
#define _EPOCH_CNT 5;
#define _DROP_RATE 0.0;

void lsp_set_epoch_lth(double lth);
void lsp_set_epoch_cnt(int cnt);
void lsp_set_drop_rate(double rate);

class LSP
{
private:
	LSP(const LSP& that); // Disallow Copy Constructor
	LSP& operator=(const LSP&); // Disallow assignment operator

protected:
	Connector connector;

	/* This is the thread that will listen to all incoming activity. */
	pthread_t listener_thread;

public:
	LSP(bool isServer) : connector(isServer) {}

	virtual ~LSP()
	{

	}
};

class LSP_Server : public LSP
{
private:

public:
	LSP_Server() : LSP(true) {}

	void create(int port);
	int  read(void* pld, uint32_t* conn_id);
	bool write(void* pld, int lth, uint32_t conn_id);
	// bool close(uint32_t conn_id);

	void init()
	{
		connector.setup(NULL, SERVER_PORT);
		connector.listen();
	}

	virtual ~LSP_Server()
	{

	}
};


class LSP_Client : public LSP
{
public:
	LSP_Client() : LSP(false) {}
	void create(const char* dest, int port);

	int read(uint8_t* pld);
	bool write(uint8_t* pld, int lth);
	bool close();

	void init()
	{
		connector.setup(LOCALHOST, SERVER_PORT);
		connector.send_message("test");
	}

	virtual ~LSP_Client()
	{

	}
};

class LSP_Worker : public LSP_Client
{

};

class LSP_Requester : public LSP_Client
{

};

#endif
