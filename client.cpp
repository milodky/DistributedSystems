#include "lsp.h"


void connect()
{
	int sock;
	struct sockaddr_in server_addr;
	struct hostent *host;
	char send_data[1024];

	host = (struct hostent *) gethostbyname((char *) DEFAULT_HOST);

	if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		perror("socket");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(DEFAULT_PORT);
	server_addr.sin_addr = *((struct in_addr *) host->h_addr);
	bzero(&(server_addr.sin_zero), 8);

   while (1)
   {
		printf("Type Something (q or Q to quit):");
		gets(send_data);

		if ((strcmp(send_data , "q") == 0) || strcmp(send_data , "Q") == 0)
		   break;
		else
		   sendto(sock, send_data, strlen(send_data), 0,
				  (struct sockaddr *)&server_addr, sizeof(struct sockaddr));
   }

}

int main ()
{
	connect();
	return 0;
}
