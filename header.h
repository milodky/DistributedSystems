#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <errno.h>
#include <strings.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <assert.h>
#include <stdarg.h>

#pragma GCC diagnostic ignored "-Wwrite-strings"

#define LOCALHOST "localhost"

#define SERVER_ADDR LOCALHOST
#define SERVER_PORT "5001"

const int BAD_SOCKFD = -1;

#define SUCCESS 0
#define FAILURE 1

#define MAX_MSG_SIZE 1024

/* Class Declarations */
struct _LSPMessage;
class LSP;

class Uncopyable
{
private:
	Uncopyable(const Uncopyable& that); // Disallow Copy Constructor
	Uncopyable& operator=(const Uncopyable&); // Disallow assignment operator

public:
	Uncopyable() {}
};

class LSP_Packet : public Uncopyable
{
private:
	int conn_id;
	int seq_no;

	char* bytes;
	int len;

public:
	LSP_Packet(int conn_id, int seq_no, char* bytes, int len)
		: conn_id(conn_id), seq_no(seq_no), len(len)
	{
		this->bytes = new char[len];
		memcpy(this->bytes, bytes, len);
	}

	~LSP_Packet()
	{
		if (bytes) delete bytes;
	}
};

/* Function Declarations */
void Error(const char *str, ...);
void pprint(_LSPMessage* msg);

#endif
