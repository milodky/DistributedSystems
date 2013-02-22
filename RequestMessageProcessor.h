#ifndef REQUESTMESSAGEPROCESSOR_H
#define REQUESTMESSAGEPROCESSOR_H

#include "MessageProcessor.h"

/* This class implements how a particular data packet has to be handled by a request client */
class RequestMessageProcessor : public MessageProcessor
{
private:
	/* The hash that was given in the command line by the user */
	const char* hashMsg;
	/* The passowrd length that was given in the command line by the user */
	unsigned password_length;

public:
	RequestMessageProcessor(Inbox* in, vector<ConnInfo*> *infos, pthread_mutex_t& mutex_connInfos);

	/* A wrapper to decide what is the course of action for different incoming message packets */ 
	virtual int process_incoming_msg(LSP_Packet& packet);
	
	/* Actions to be taken if a packet is found or not */
	virtual int process_data_packet(LSP_Packet& packet);
	
	/* Actions to be taken if a packet is an ack packet */
	virtual int process_ack_packet(LSP_Packet& packet);
	
	/* Assigning the private data memebers in this class */
	void set_password_data(const char* const hashMsg, const unsigned len);

	/* Creating the crack request packet that is to be sent to the server */
	LSP_Packet create_crack_req_packet();

	virtual ~RequestMessageProcessor();
};
#endif
