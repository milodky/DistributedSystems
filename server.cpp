#include "lsp.h"
#include "connectionInfo.h"

using namespace std;
void connect()
{
	LSP_Server server;
	server.init();
}

void outboxPoller()
{

}

void Sender()
{

	vector<ConnInfo*> clients;
	ConnInfo o(0,12,(string)"Host 1");
	clients.push_back(&o);
	ConnInfo o1(1,1,(string)"Host2");
	clients.push_back(&o1);
	for(int j=0;j<clients.size();++j)
	{
		clients[j]->addPacket(0,0,(uint8_t*)"Hello");
		if(j!=0)
			clients[j]->msgSent = true;

	}
	for(int j=0;j<clients.size();++j)
	{
		if(clients[j]->msgSent==false && clients[j]->outMsgs.size()!=0)
			break;
			//clients[j]->outMsgs.front()<<endl;
	}
}


int main ()
{

	Sender();
	//connect();
	return 0;
}

