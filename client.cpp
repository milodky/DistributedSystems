#include "lsp.h"


void connect()
{
	LSP_Client client;
	client.connect();
	client.run();
}

int main ()
{
	connect();
	return 0;
}
