#ifndef EPOCH_H
#define EPOCH_H

#include "header.h"

class Epoch : public Uncopyable
{
protected:
	LSP* lsp;

public:
	Epoch(LSP* lsp);

	virtual ~Epoch();
};

class EpochServer : public Epoch
{
private:

public:
	EpochServer(LSP* lsp);

	LSP_Server* get_lsp();

	virtual ~EpochServer();
};

class EpochClient: public Epoch
{
private:

public:
	EpochClient(LSP* lsp);

	LSP_Client* get_lsp();

	virtual ~EpochClient();
};
#endif
