#ifndef INBOX_H
#define INBOX_H

#include "lsp.h"

class Epoch : public Uncopyable
{
protected:
	LSP* lsp;

public:
	Epoch(LSP* lsp);

	~Epoch();
};

class EpochServer : public Epoch
{
private:

public:
	EpochServer();

	LSP_Server* get_lsp();

	~EpochServer();
};

class EpochClient: public Epoch
{
private:

public:
	EpochClient();

	LSP_Client* get_lsp();

	~EpochClient();
};
#endif
