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
	hints.ai_family = AF_INET; // Mention IP4 else data is not read properly!

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

int Connector::setup(char* const host, char* const portStr)
{
	populateAddrInfo(host, portStr);

	// loop through all the results and bind to the first we can
	struct addrinfo* p;
	for(p = addressInfoPtr; p != NULL; p = p->ai_next)
	{
		if (createSocket(p))
		{
			if(isServer)
			{
				if(bindToPort(p))
				{
					break;
				}
				else
				{
					fprintf(stderr, "Closing socket: %d/n", sockfd);
					close(sockfd);
					sockfd = BAD_SOCKFD;
				}
			}
			else
			{
				break;
			}
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

// get sockaddr, IPv4 or IPv6:
void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET) {
		return &(((struct sockaddr_in*)sa)->sin_addr);
	}
	return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int Connector::listen()
{
	if (sockfd == BAD_SOCKFD)
	{
		return FAILURE;
	}

	int 				bytes_read;
	char 				recv_data[MAX_MSG_SIZE];
	const int FLAGS = 0;
	struct sockaddr_storage from_addr;
	socklen_t fromlen;

	char from_ipv4[INET_ADDRSTRLEN];

	printf("\nServer Waiting..\n");
	fflush(stdout);

	while (1)
	{
		fromlen = sizeof from_addr;
		bytes_read = recvfrom(sockfd,
				recv_data, MAX_MSG_SIZE, FLAGS,
				(struct sockaddr *) &from_addr, &fromlen);

		if (bytes_read == -1)
		{
			perror("recvfrom");
			return FAILURE;
		}

		recv_data[bytes_read] = '\0';
		inet_ntop(AF_INET,
						get_in_addr((struct sockaddr *)&from_addr),
						from_ipv4, sizeof from_ipv4);

		printf("[%s : %d] said: ", from_ipv4,
						ntohs(((struct sockaddr_in *) &from_addr)->sin_port));

		printf("%s\n", recv_data);

		fflush(stdout);
	}
	return 0;
}

/**
 * Default send: send to server
 */
int Connector::send_message(uint8_t* const msg, const int len)
{
	if (sockfd == BAD_SOCKFD)
	{
		return FAILURE;
	}
	// assert (!isServer);

	if (sendto(sockfd, msg, len, 0,
			ai_node->ai_addr, ai_node->ai_addrlen) == -1)
	{
		perror("talker: sendto");
	}
	return SUCCESS;
}

/**
 * Explicitly mention the recipient hostname and recipient port.
 * Same socket can be used to send to different recipients.
 */
int Connector::send_message(char* const recvr_hostname, const int recvr_port, uint8_t* const msg, const int len)
{
	if (sockfd == BAD_SOCKFD)
	{
		return FAILURE;
	}
	//assert (isServer);

	struct sockaddr_in recvr_addr;
	struct hostent *host;

	host = (struct hostent *) gethostbyname((char *) recvr_hostname);

	recvr_addr.sin_family = AF_INET;
	recvr_addr.sin_port = htons(recvr_port);
	recvr_addr.sin_addr = *((struct in_addr *) host->h_addr);
	bzero(&(recvr_addr.sin_zero), 8);

	if (sendto(sockfd, msg, len, 0,
			(struct sockaddr *)&recvr_addr, sizeof(struct sockaddr)) == -1)
	{
		perror("talker: sendto");
	}
	return SUCCESS;
}
