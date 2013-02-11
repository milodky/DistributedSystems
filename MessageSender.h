#ifndef MESSAGESENDER_H
#define MESSAGESENDER_H

#include "header.h"
#include "connection.h"
#include "inbox.h"
#include "serializer.h"
#include "connectionInfo.h"

class MessageSender : public Uncopyable
{
private:
	Connector *connector;
	Serializer serializer;
	//vector<ConnInfo> connectionInfo;

public:

	void send_msg(ConnInfo cInfo)
	{
		//Marshals and sends the message.
		LSP_Packet packet = cInfo.outMsgs.front();
		Serializer s;
		uint8_t *buf;
		int len = s.marshal(packet,buf);
		if(connector->isServer)
			connector->send_message(cInfo.hostName,
					cInfo.port, buf, len);
		else
			connector->send_message(buf,len);
		free(buf);
	}
};

#endif
