#include "lsp.h"
#include "serializer.h"

using namespace std;
void connect()
{
	LSP_Server server;
	server.init();
}

class ConnInfo : public Uncopyable
{
private:
public:
	string hostName;
	int port;
	int connectionID;
	//might have to be made volatile
	int epochsSinceMsgRcd;
	int epochsSinceMsgSent;
	int countMsgsRcd;
	int countMsgsSent;
	bool isAlive;
	bool msgSent;
	queue<LSP_Packet> outMsgs;

	ConnInfo(int connId, int p, string host) : connectionID(connId), port(p), hostName(host)
	{
		//default values when constructed.
		msgSent = false; //Only now connection request has come in. So msgSent will be false.
		isAlive = true;  //Assumed alive since connection request has just come in.
		//change these based on client and server
		countMsgsRcd = 1; //only connection request is got at this point.
		countMsgsSent = 0;
		epochsSinceMsgRcd = 0;
		epochsSinceMsgSent = 0;
	}
	void addPacket(int seqNo, size_t len, uint8_t *bytes)
	{
		//Gets the message, marshalls it with relevant info and pushes to queue.
		LSP_Packet packet(connectionID, seqNo, len, bytes);
		outMsgs.push(packet);
	}
	void SendMsg(Connector connector)
	{
		LSP_Packet packet = outMsgs.front();
		Serializer s;
		uint8_t *buf;
		int len = s.marshal(packet,buf);
		connector.send_message(buf,len);
		free(buf);
	}
};

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

