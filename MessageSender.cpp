#include "MessageSender.h"

void MessageSender::send_msg(ConnInfo &cInfo)
{
		//Marshals and sends the message.
		LSP_Packet packet = cInfo.outMsgs.front();
		uint8_t *buf;
		int len = serializer.marshal(packet,buf);
		if(connector->getIsServer())
			connector->send_message(cInfo.hostName,
					cInfo.port, buf, len);
		else
			connector->send_message(buf,len);
		cInfo.msgSent = true;
		printf("Message Sent");
		free(buf);
}

void MessageSender::pollToSend(vector<ConnInfo*>* connectionInfo)
{
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

