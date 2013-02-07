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
private:
	struct addrinfo*	addressInfoPtr; // Filled up by system call getaddrinfo

protected:
	struct addrinfo*	ai_node; // The node which is currently being used
	int 				sockfd; // A nonnegative socket file descriptor indicates success

public:
	/**
	 * Populate addressInfoPtr
	 */
	bool populateAddrInfo(char* const host, char* const portStr);
	bool createSocket(struct addrinfo* const addressInfoPtr);
	bool bindToPort(struct addrinfo* const addressInfoPtr);
	int setupListener(char* const portStr);
	int setupTalker(char* const host, char* const portStr);

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

	int connect()
	{
		return setupTalker(LOCALHOST, SERVER_PORT);
	}

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

	/*
	int recvtimeout(int s, int timeout)
	{
		fd_set fds;
		int n;
		struct timeval tv;
		// set up the file descriptor set
		FD_ZERO(&fds);
		FD_SET(s, &fds);
		// set up the struct timeval for the timeout
		tv.tv_sec = timeout;
		tv.tv_usec = 0;
		// wait until timeout or data received
		n = select(s+1, &fds, NULL, NULL, &tv);
		if (n == 0) return -2; // timeout!
		if (n == -1) return -1; // error
		// data must be here, so do a normal recv()
		return 0;
	}
	*/

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
			printf("%s\n", recv_data);

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
