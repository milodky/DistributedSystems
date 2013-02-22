#include <openssl/sha.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char **argv)
{
	if(argc!=2)
	{
		printf("Incorrect usage. Please use format as below.\n");
		printf("./SHA password\n");
		return 1;
	}

	int i = 0;
	unsigned char temp[SHA_DIGEST_LENGTH];
	char buf[SHA_DIGEST_LENGTH*2];

	memset(buf, 0x0, SHA_DIGEST_LENGTH*2);
	memset(temp, 0x0, SHA_DIGEST_LENGTH);
	char* password = argv[1];

	SHA1((unsigned char *)password, strlen(password), temp);

	for (i=0; i < SHA_DIGEST_LENGTH; i++) {
		sprintf((char*)&(buf[i*2]), "%02x", temp[i]);
	}

	printf("request localhost:5000 %s %d\n", buf, strlen(password));
	return 0;
}
