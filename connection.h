#ifndef CONNECTION_H
#define CONNECTION_H

#include "header.h"

class Connector
{
private:

protected:
	struct addrinfo*	addressInfoPtr; // Filled up by system call getaddrinfo
	struct addrinfo*	ai_node; // The node which is currently being used
	int 				sockfd; // A nonnegative socket file descriptor indicates success

public:
	/**
	 * Populate addressInfoPtr
	 */
	bool populateAddrInfo(char* const host, char* const portStr);
	bool createSocket(struct addrinfo* const addressInfoPtr);
	bool bindToPort(struct addrinfo* const addressInfoPtr);

	virtual ~Connector()
	{
		/* This data structure is no longer required */
		if (addressInfoPtr) freeaddrinfo(addressInfoPtr);
		if(sockfd != BAD_SOCKFD)
			close(sockfd);
	}
};

class Listener : public Connector
{
private:

protected:

public:
	int connect()
	{
		return setup(SERVER_PORT);
	}

	int setup(char* const portStr);
	int listen();

	virtual ~Listener()
	{

	}
};

class Talker :public Connector
{
private:

protected:

public:
	int connect()
	{
		return setup(LOCALHOST, SERVER_PORT);
	}

	int setup(char* const host, char* const portStr);

	/**
	 * Default send: send to server
	 */
	void send_message(char* const msg)
	{
		if (sendto(sockfd, msg, strlen(msg), 0,
				ai_node->ai_addr, ai_node->ai_addrlen) == -1)
		{
			perror("talker: sendto");
		}
	}

	/**
	 * Explicitly mention the recipient hostname and recipient port.
	 * Same socket can be used to send to different recipients.
	 */
	void send_message(char* const recvr_hostname, const int recvr_port, char* const msg)
	{
		struct sockaddr_in recvr_addr;
		struct hostent *host;

		host = (struct hostent *) gethostbyname((char *) recvr_hostname);

		recvr_addr.sin_family = AF_INET;
		recvr_addr.sin_port = htons(recvr_port);
		recvr_addr.sin_addr = *((struct in_addr *) host->h_addr);
		bzero(&(recvr_addr.sin_zero), 8);

		if (sendto(sockfd, msg, strlen(msg), 0,
				(struct sockaddr *)&recvr_addr, sizeof(struct sockaddr)) == -1)
		{
			perror("talker: sendto");
		}
	}

	virtual ~Talker()
	{

	}
};

#endif
