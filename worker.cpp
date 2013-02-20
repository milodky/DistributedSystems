#include <iostream>
#include <sstream>
#include <string>

#include "lsp_client.h"

using namespace std;

void connect(char* host, char *port)
{
	LSP_Worker worker(host,port);
	worker.init();
	worker.run();
}

int main(int argc, char** argv)
{
	srand(12345);
	if(argc!=2)
	{
		printf("Incorrect usage. Please use format as below.\n");
		printf("./worker host:port\n");
		return 1;
	}
	try
	{
		char* t1 = strtok(argv[1],":");
		char* host = t1;
		t1 = strtok(NULL,":");
		if(t1 == NULL) throw "Exception";
		char* port = t1;
		connect(host,port);
		return 0;
	}
	catch(...)
	{
		printf("Incorrect usage. Please use format as below.\n");
		printf("./worker host:port\n");
		return 1;
	}
}
