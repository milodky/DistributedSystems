#include "lsp.h"
#include "connectionInfo.h"

using namespace std;
void connect(char* port)
{
	LSP_Server server(port);
	server.init();
}

void Sender()
{

//	vector<ConnInfo*> clients;
//	ConnInfo o(0,12,"Host 1");
//	clients.push_back(&o);
//	ConnInfo o1(1,1,"Host2");
//	clients.push_back(&o1);
//	for(int j=0;j<clients.size();++j)
//	{
//		clients[j]->addPacket(0,0,(uint8_t*)"Hello");
//		if(j!=0)
//			clients[j]->msgSent = true;
//
//	}
//	for(int j=0;j<clients.size();++j)
//	{
//		if(clients[j]->msgSent==false && clients[j]->getOutMsgsCount()!=0)
//			break;
//	}
}


int main (int argc, char* const argv[])
{
	if(argc!=2)
	{
		printf("Incorrect usage. Please use format as below.\n");
		printf("./server port\n");
		return 1;
	}
	connect(argv[1]);
	return 0;
}

