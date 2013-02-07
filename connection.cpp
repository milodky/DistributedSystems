#include "connection.h"


/**
 * Populate addressInfoPtr
 */
bool Connector::populateAddrInfo(char* const host, char* const portStr)
{
	fprintf(stderr, "Populating Address Info.. ");

	int status;
	struct addrinfo hints;

	memset(&hints, 0, sizeof hints); // make sure the struct is empty
	hints.ai_family = AF_UNSPEC; // don't care IPv4 or IPv6

	hints.ai_socktype = SOCK_DGRAM; // UDP datagrams
	/**
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

bool Connector::createSocket(struct addrinfo* const addressInfoPtr)
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

bool Connector::bindToPort(struct addrinfo* const addressInfoPtr)
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

int Listener::setup(char* const portStr)
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
	ai_node = p;
	return 0;
}

int recvtimeout(int sockfd, int timeout)
{
	fd_set fds;
	int n;
	struct timeval tv;

	// set up the file descriptor set
	FD_ZERO(&fds);
	FD_SET(sockfd, &fds);

	// set up the struct timeval for the timeout
	tv.tv_sec = timeout;
	tv.tv_usec = 0;

	// wait until timeout or data received
	n = select(sockfd + 1, &fds, NULL, NULL, &tv);

	if (n == 0) return -2; // timeout!
	else if (n == -1) return -1; // error
	else return 0;
}

int Listener::listen()
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

int Talker::setup(char* const host, char* const portStr)
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
	ai_node = p;
	return 0;
}
