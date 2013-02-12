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
	vector<ConnInfo*> *connectionInfo;

public:

	MessageSender(vector<ConnInfo*> *info, Connector * conn) : connectionInfo(info),connector(conn)
	{	}

	void send_msg(ConnInfo &cInfo);
	void pollToSend(vector<ConnInfo*>* connectionInfo);
};

#endif
