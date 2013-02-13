#include <iostream>
#include <sstream>
#include <string>
//using namespace std
#include "lsp.h"

using namespace std;

string numToString(int x,int length)
{
	string str = "";
	int y;
	do {
		y=x%26;
		str=char('a'+y) +str;
		x/=26;
	}while(x);
	str.insert(0,length-str.length(),'a');
	return str;
}

void searchIn(string password, int start, int end, int length)
{
	for(int i = start; i < end; i++)
	{
		string str = numToString(i,length);
		cout << str << endl;
		if(str.compare(password)==0)
		{
			cout<<"Password Matched!  " << str <<endl;
			break;
		}
	}
}

void connect(char* host, char *port)
{
	LSP_Worker worker(host,port);
	worker.init();
	worker.run();
}

int main(int argc, char** argv)
{
	if(argc!=2)
	{
		printf("Incorrect usage. Please use format as below.\n");
		printf("./worker host:port\n");
		return 1;
	}

	char* t1 = strtok(argv[1],":");
	char* host = t1;
	t1 = strtok(NULL,":");
	char* port = t1;
	cout<<port<<endl;
	connect(host,port);
	int i = 0;
	unsigned char temp[SHA_DIGEST_LENGTH];
	char buf[SHA_DIGEST_LENGTH*2];

	memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
	memset(temp, 0x0, SHA_DIGEST_LENGTH);
	char* password = "aadef";

	SHA1((unsigned char *)password, strlen(password), temp);

	for (i=0; i < SHA_DIGEST_LENGTH; i++) {
		sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
	}

	printf("SHA1 of %s is %s\n", password, buf);
	return 0;
}
