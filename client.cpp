#include "lsp.h"


void connect(char* host, char *port, char* hash, char* len)
{
	LSP_Requester request(host,port,hash,atoi(len));
	request.init();
	request.run();
	/*
	LSP_Client client;
	client.connect();
	char send_data[1024];

	while (1)
	{
		printf("Type Something (q or Q to quit):");
		gets(send_data);

		if ((strcmp(send_data , "q") == 0) || strcmp(send_data , "Q") == 0)
			break;
		else
			client.send_message(LOCALHOST, 5000, send_data);
	}
	*/
}

int main (int argc, char* const argv[])
{
	if(argc!=4)
	{
		printf("Incorrect usage. Please use format as below.\n");
		printf("./request host:port hash len\n");
		return 1;
	}

	char* temp = strtok(argv[1],":");
	char* host = temp;
	temp = strtok(NULL,":");
	char* port = temp;
	char* hash = argv[2];
	char* len = argv[3];

	printf("Request Client initiated...\n");
	printf("Connecting to %s : %s\n", host, port);

	connect(host,port,hash,len);
	return 0;
}
