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
	/* Marshall and send the message using the connection layer */
	void send_msg(ConnInfo &cInfo);
	/* Poll over the outbox and check if there is any packet to be sent */
	void pollToSend(vector<ConnInfo*>* connectionInfo);
};

#endif
