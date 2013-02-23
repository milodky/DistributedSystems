#include <signal.h>

#include "lsp_server.h"
#include "connectionInfo.h"
using namespace std;

extern bool destroy_thread;

//void test_api(char* port)
//{
//	lsp_server* a_srv = lsp_server_create(atoi(port));
//
//	if (a_srv != NULL)
//	{
//		delete a_srv->server;
//		free(a_srv);
//	}
//}

void connect(char* port)
{
	/* Initializes the worker and starts running */
	LSP_Server server(port);
	server.init();
	server.run();
}

int main (int argc, char* const argv[])
{
	srand(12345);
	if(argc!=2)
	{
		printf("Incorrect usage. Please use format as below.\n");
		printf("./server port\n");
		return 1;
	}
	try
	{
	/* Checks if input is given in correct format */
	connect(argv[1]);
	return 0;
	}
	catch(...)
	{
		printf("Incorrect usage. Please use format as below.\n");
		printf("./server port\n");
		return 1;
	}
}

// Code for API testing
//int main(int argc, char* const argv[])
//{
////	signal(SIGABRT, &sighandler);
////	signal(SIGTERM, &sighandler);
////	signal(SIGINT, &sighandler);
//	lsp_server* myserver = lsp_server_create(atoi(argv[1]));
//
//	uint8_t payload[4096];
//	uint32_t returned_id;
//	while(true)
//	{
//		int bytes = lsp_server_read(myserver, payload, &returned_id);
//		//sleep(50);
//		lsp_server_write(myserver, NULL, 0, returned_id);
//		if(bytes > 0 )
//		{
//			printBytes(payload,bytes);
//		}
//	}
//	printf("Exiting\n");
//
//}
