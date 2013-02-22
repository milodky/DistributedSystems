#include <signal.h>

#include "lsp_server.h"
#include "connectionInfo.h"

using namespace std;

extern bool destroy_thread;

void test_api(char* port)
{
	lsp_server* a_srv = lsp_server_create(atoi(port));

	if (a_srv != NULL)
	{
		delete a_srv->server;
		free(a_srv);
	}
}

void connect(char* port)
{
	LSP_Server server(port);
	server.init();
	server.run();
}

void sighandler(int p)
{
	destroy_thread = true;
}

int main (int argc, char* const argv[])
{
	srand(12345);

//	signal(SIGABRT, &sighandler);
//	signal(SIGTERM, &sighandler);
//	signal(SIGINT, &sighandler);

	if(argc!=2)
	{
		printf("Incorrect usage. Please use format as below.\n");
		printf("./server port\n");
		return 1;
	}
	try
	{
		test_api(argv[1]);
		return 0;
	}
	catch(...)
	{
		printf("Incorrect usage. Please use format as below.\n");
		printf("./server port\n");
		return 1;
	}
}

