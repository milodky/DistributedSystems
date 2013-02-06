/**
 * Header file for lsp protocol
 *
 */

#ifndef LSP_H
#define LSP_H

#include "header.h"

// Global Parameters. For both server and clients.

#define _EPOCH_LTH 2.0
#define _EPOCH_CNT 5;
#define _DROP_RATE 0.0;

void lsp_set_epoch_lth(double lth);
void lsp_set_epoch_cnt(int cnt);
void lsp_set_drop_rate(double rate);

class LSP
{
protected:
	struct addrinfo*	addressInfoPtr; // Filled up by system call getaddrinfo
	int 				sockfd; // A nonnegative socket file descriptor indicates success

public:
	/**
	 * Populate addressInfoPtr
	 */
	bool populateAddrInfo(char* const host, char* const portStr)
	{
		fprintf(stderr, "Populating Address Info.. ");

		int status;
		struct addrinfo hints;

		memset(&hints, 0, sizeof hints); // make sure the struct is empty
		hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6

		hints.ai_socktype = SOCK_DGRAM; // UDP datagrams
		/*
		 * By using the AI_PASSIVE flag, I'm telling the program to bind
		 * to the IP of the host it's running on. If you want to bind to
		 * a specific local IP address, drop the AI_PASSIVE and put an
		 * IP address in for the first argument to getaddrinfo()
		 * */
		hints.ai_flags = AI_PASSIVE; // fill in my IP for me

		if ((status = getaddrinfo(host, portStr, &hints, &addressInfoPtr)) != 0)
		{
			fprintf(stderr, "\npopulateAddrInfo() :: getaddrinfo error: %s\n", gai_strerror(status));
			return false;
		}
		fprintf(stderr, "Done.\n");
		return true;
	}

	bool createSocket(struct addrinfo* const addressInfoPtr)
	{
		fprintf(stderr, "Creating a socket.. ");
		if ((sockfd = socket(addressInfoPtr->ai_family, addressInfoPtr->ai_socktype, addressInfoPtr->ai_protocol)) == -1)
		{
			printf("\n");
			perror("Socket");
			return false;
		}
		fprintf(stderr, "Done.\n");
		return true;
	}

	bool bindToPort(struct addrinfo* const addressInfoPtr)
	{
		fprintf(stderr, "Binding to port.. ");
		if (bind(sockfd, addressInfoPtr->ai_addr, addressInfoPtr->ai_addrlen) == -1)
		{
			perror("Bind");
			return false;
		}
		fprintf(stderr, "Done.\n");
		return true;
	}

	int setupListener(char* const portStr)
	{
		populateAddrInfo(LOCALHOST, portStr);

		// loop through all the results and bind to the first we can
		struct addrinfo* p;
		for(p = addressInfoPtr; p != NULL; p = p->ai_next)
		{
			if (createSocket(p))
				if(bindToPort(p))
					break;
				else
				{
					fprintf(stderr, "Closing socket: %d/n", sockfd);
					close(sockfd);
					sockfd = BAD_SOCKFD;
				}
		}

		if (p == NULL)
		{
			fprintf(stderr, "listener: failed to bind socket\n");
			return 2;
		}
		return 0;
	}

	int setupTalker(char* const host, char* const portStr)
	{
		populateAddrInfo(host, portStr);

		// loop through all the results and bind to the first we can
		struct addrinfo* p;
		for(p = addressInfoPtr; p != NULL; p = p->ai_next)
		{
			if (createSocket(p))
				break;
		}

		if (p == NULL)
		{
			fprintf(stderr, "listener: failed to bind socket\n");
			return 2;
		}
		return 0;
	}

	virtual ~LSP()
	{
		/* This data structure is no longer required */
		if (addressInfoPtr) freeaddrinfo(addressInfoPtr);
	}
};


class LSP_Client : public LSP
{
public:

	void create(const char* dest, int port);

	int read(uint8_t* pld);
	bool write(uint8_t* pld, int lth);
	bool close();

	virtual ~LSP_Client()
	{

	}
};

class LSP_Worker : public LSP
{

	void create(const char* dest, int port);

	int read(uint8_t* pld);
	bool write(uint8_t* pld, int lth);
	bool close();
};

class LSP_Server : public LSP
{
private:

public:
	void create(int port);
	int  read(void* pld, uint32_t* conn_id);
	bool write(void* pld, int lth, uint32_t conn_id);
	// bool close(uint32_t conn_id);

	int connect()
	{
		return setupListener(SERVER_PORT);
	}

	int run()
	{
		unsigned int 		addr_len;
		int 				bytes_read;
		char 				recv_data[1024];
		struct sockaddr_in 	server_addr, client_addr;
		char 				client_ipv4[INET_ADDRSTRLEN];

		addr_len = sizeof(struct sockaddr);

		printf("\nUDP Server Waiting for client on port 5000\n");
		fflush(stdout);

		while (1)
		{
			bytes_read = recvfrom(sockfd, recv_data, 1024, 0,
					  (struct sockaddr *) &client_addr, &addr_len);

			recv_data[bytes_read] = '\0';

			inet_ntop(AF_INET, &(client_addr.sin_addr), client_ipv4, INET_ADDRSTRLEN);

			printf("\n(%s , %d) said : ", client_ipv4, ntohs(client_addr.sin_port));
			printf("%s", recv_data);

			fflush(stdout);

		}
		return 0;
	}

	virtual ~LSP_Server()
	{
		if(sockfd != BAD_SOCKFD)
			close(sockfd);
	}
};

#endif
