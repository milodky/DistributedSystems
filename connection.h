#ifndef CONNECTION_H
#define CONNECTION_H

#include "header.h"

class Connector
{
private:
	bool isServer;

	Connector(const Connector& that);  // Disallow Copy Constructor
	Connector& operator=(const Connector&); // Disallow assignment operator

protected:
	struct addrinfo*	addressInfoPtr; // Filled up by system call getaddrinfo
	struct addrinfo*	ai_node; // The node which is currently being used
	int 				sockfd; // A nonnegative socket file descriptor indicates success

public:
	/**
	 * Public Constructor
	 */
	Connector(bool isServer) : isServer(isServer)
	{
		addressInfoPtr = NULL;
		ai_node = NULL;
		sockfd = BAD_SOCKFD;
	}

	/**
	 * Populate addressInfoPtr
	 */
	bool populateAddrInfo(char* const host, char* const portStr);
	bool createSocket(struct addrinfo* const addressInfoPtr);
	bool bindToPort(struct addrinfo* const addressInfoPtr);

	/**
	 * Initializes the sockets. Binds only if its a server.
	 */
	int setup(char* const host, char* const portStr);

	/**
	 * Runs infinitely. Waits and receives each incoming message.
	 */
	int listen();
	/**
	 * Default send: send to server
	 */
	void send_message(char* const msg);

	/**
	 * Explicitly mention the recipient hostname and recipient port.
	 * Same socket can be used to send to different recipients.
	 */
	void send_message(char* const recvr_hostname, const int recvr_port, char* const msg);

	virtual ~Connector()
	{
		/* This data structure is no longer required */
		if (addressInfoPtr) freeaddrinfo(addressInfoPtr);
		if(sockfd != BAD_SOCKFD)
			close(sockfd);
	}
};

#endif
