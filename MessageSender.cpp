#include "MessageSender.h"

MessageSender::MessageSender(vector<ConnInfo*> *info, Connector * conn)
: connectionInfo(info),connector(conn)
{

}

void MessageSender::send_msg(ConnInfo &cInfo)
{
	//Marshals and sends the message.
	LSP_Packet packet = cInfo.get_front_msg();
	uint8_t *buf;
	int len = serializer.marshal(packet,buf);
	if(connector->getIsServer())
	{
		connector->send_message(cInfo.getHostName(), cInfo.getPort(), buf, len);
		fprintf(stderr, "MessageSender:: Message sent to %s : %d\n", cInfo.getHostName(), cInfo.getPort());
	}
	else
	{
		connector->send_message(buf,len);
		fprintf(stderr, "MessageSender:: Message sent to server.\n");
	}
	cInfo.setMsgSent(true);
	free(buf);
}

void MessageSender::pollToSend(vector<ConnInfo*>* connectionInfo)
{
	fprintf(stderr, "MessageSender:: Polling from outbox...\n");
	while(1)
	{
		for(vector<ConnInfo*>::iterator it=connectionInfo->begin();
				it!=connectionInfo->end(); ++it)
		{
			if((*it)->isMsgToBeSent())
				send_msg(**it);
		}
	}
}

