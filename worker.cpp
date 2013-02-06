#include <iostream>
#include <string>
#include <openssl/sha.h>
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

void searchIn(string password, int start, int count, int length)
{
	for(int i = start; i < count; i++)
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

int main(int argn, char** argv)
{
	//int a = 2137;
	//cout << numToString(a,5);
	//searchIn("aadef",2000,2200,5);
	//return 0;

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
