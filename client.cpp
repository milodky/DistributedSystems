#include "lsp_client.h"

void connect(char* host, char *port, char* hash, char* len)
{
	LSP_Requester request(host,port,hash,atoi(len));
	request.init();
	request.run();
}

int main (int argc, char* const argv[])
{
	srand(12345);
	if(argc!=4)
	{
		printf("Incorrect usage. Please use format as below.\n");
		printf("./request host:port hash len\n");
		return 1;
	}
	try
	{
		char* temp = strtok(argv[1],":");
		char* host = temp;
		temp = strtok(NULL,":");
		if(temp == NULL) throw "Exception";
		char* port = temp;
		char* hash = argv[2];
		char* len = argv[3];

		printf("Request Client initiated...\n");
		printf("Connecting to %s : %s\n", host, port);

		connect(host,port,hash,len);
		return 0;
	}
	catch(...)
	{
		printf("Incorrect usage. Please use format as below.\n");
		printf("./request host:port hash len\n");
		return 1;
	}


}

// Code for API testing
//int main(int argc, char* const argv[])
//{
//	lsp_client *myclient = lsp_client_create("localhost",atoi(argv[1]));
//
//	char message[] = "";
//	lsp_client_write(myclient, NULL, 0);
//
//	uint8_t buffer[4096];
//
//
//
////	printBytes(buffer1, bytes_read1);
//	int bytes_read = 0;
//	sleep(5);
//	//while(bytes_read == 0)
//		bytes_read = lsp_client_read(myclient, buffer);
//
//
//	char message1[] = "j";
//	lsp_client_write(myclient, (uint8_t*) message1, strlen(message1)+1);
//	uint8_t buffer1[4096];
//	int bytes_read1 = 0;
//	while(bytes_read1 == 0)
//		bytes_read1 = lsp_client_read(myclient, buffer1);
//
//	//printBytes(buffer, bytes_read);
//	lsp_client_close(myclient);
//}
