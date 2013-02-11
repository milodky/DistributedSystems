#include "lsp.h"

void connect()
{
	LSP_Server server;
	server.init();
}

class Outbox
{
private:
	Outbox(const Outbox& that);
	Outbox& operator=(const Outbox&);

public:
	string hostName;
	int port;
	int connectionID;
	//might have to be made volatile
	int epochsSinceMsgRcd;
	int epochsSentCount;
	int countMsgsRcd;
	bool isAlive;
	bool msgSent;
	queue<string> outboxQ;
	//wont be string. struct - sent or not sent

	Outbox(int connId, int p, string host)
	{
		connectionID = connId;
		port = p;
		hostName = host;
		//default values when constructed.
		msgSent = false; //Only now connection request has come in. So msgSent will be false.
		isAlive = true;  //Assumed alive since connection request has just come in.
		countMsgsRcd = 1; //only connection request is got at this point.
		epochsSinceMsgRcd = 0;
		epochsSentCount = 0;
	}

	void addMessageToOutbox (string msg)
	{
		outboxQ.push(msg);
	}
	void marshal(){}
};

void Sender()
{
	vector<Outbox*> clients;
	queue<string> i;
	Outbox o(0,12,"Host 1");
	clients.push_back(&o);
	Outbox o1(1,1,"Host2");
	clients.push_back(&o1);
	for(int j=0;j<clients.size();++j)
	{
		clients[j]->addMessageToOutbox("Hello");
		if(j!=0)
			clients[j]->msgSent = true;

	}
	for(int j=0;j<clients.size();++j)
	{
		if(clients[j]->msgSent==false && clients[j]->outboxQ.size()!=0)
			//marshall message, send message, and set msgSent as true
			cout<<clients[j]->outboxQ.front()<<endl;
		clients[j]->marshal();
	}
}


int main ()
{
	Sender();
	//connect();
	return 0;
}
