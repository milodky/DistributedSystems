#include "lsp.h"
#include "connectionInfo.h"

using namespace std;
void connect(char* port)
{
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
	connect(argv[1]);
	return 0;
}

