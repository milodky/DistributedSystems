#include <iostream>
#include <sstream>
#include <string>
//using namespace std
#include "lsp.h"

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
	if(strchr(argv[1],':')==NULL)
	{
		printf("Incorrect usage. Please use format as below.\n");
		printf("./worker host:port\n");
		return 1;
	}

	char* t1 = strtok(argv[1],":");
	char* host = t1;
	t1 = strtok(NULL,":");
	char* port = t1;
	connect(host,port);
	return 0;
}
