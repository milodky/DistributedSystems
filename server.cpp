#include "lsp.h"

void connect()
{
	LSP_Server server;
	server.init();

}

int main ()
{
	connect();
	return 0;
}
