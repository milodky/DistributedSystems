#ifndef MESSAGESENDER_H
#define MESSAGESENDER_H

#include "header.h"
#include "lsppacket.h"
#include "connection.h"
#include "inbox.h"
#include "serializer.h"
#include "connectionInfo.h"

class MessageSender : public Uncopyable
{
private:
	Connector *connector;
	Serializer serializer;

	pthread_mutex_t& mutex_connInfos;
	vector<ConnInfo*> *connectionInfo;

public:

	MessageSender(vector<ConnInfo*> *info,pthread_mutex_t& mutex_connInfos, Connector * conn);
	void send_msg(ConnInfo &cInfo);
	void pollToSend(vector<ConnInfo*>* connectionInfo);
};

#endif
