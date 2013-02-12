#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include <errno.h>
#include <strings.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>
#include <assert.h>
#include <stdarg.h>
#include <queue>
#include <vector>
#include <string>
#include <exception>

using namespace std;

#pragma GCC diagnostic ignored "-Wwrite-strings"

#define LOCALHOST "localhost"

#define SERVER_ADDR LOCALHOST
#define SERVER_PORT "1040"

const int BAD_SOCKFD = -1;

#define SUCCESS 0
#define FAILURE 1

#define MAX_MSG_SIZE 1024

void printBytes(uint8_t* data, size_t len);

/* Class Declarations */
struct _LSPMessage;

class LSP;
class Inbox;
class MessageReceiver;
class Connector;
class Serializer;
class ConnInfo;
class MessageSender;

class Uncopyable
{
private:
	Uncopyable(const Uncopyable& that); // Disallow Copy Constructor
	Uncopyable& operator=(const Uncopyable&); // Disallow assignment operator

public:
	Uncopyable() {}
};

class LSP_Packet
{
private:
	int conn_id;
	int seq_no;

	size_t len;
	uint8_t* bytes;

	LSP_Packet& operator = (const LSP_Packet& that);

public:
//	LSP_Packet(): conn_id(-1), seq_no(-1)
//	{
//
//	}

	LSP_Packet(int conn_id, int seq_no, size_t len, uint8_t* bytes)
		: conn_id(conn_id), seq_no(seq_no), len(len), bytes(new uint8_t[len])
	{
		memcpy(this->bytes, bytes, len);
	}

	LSP_Packet(const LSP_Packet& that)
		: conn_id(that.conn_id), seq_no(that.seq_no), len(that.len), bytes(new uint8_t[len])
	{
		memcpy(this->bytes, that.bytes, len);
	}

	/* Please do not delete this code */
//	LSP_Packet& operator = (const LSP_Packet& that)
//	{
//		conn_id = that.conn_id;
//		seq_no = that.seq_no;
//		len = that.len;
//
//		memcpy(this->bytes, that.bytes, len);
//	}

	void print()
	{
		printf("LSP_Packet{\nconn_id: %d, seq_no: %d, len: %u\n",
				conn_id, seq_no, len);
		printBytes(bytes, len);
		printf("}\n");
	}

	~LSP_Packet()
	{
		if (bytes) delete bytes;
	}

	uint8_t* getBytes() const {
		return bytes;
	}

	int getConnId() const {
		return conn_id;
	}

	size_t getLen() const {
		return len;
	}

	int getSeqNo() const {
		return seq_no;
	}
};

/* Function Declarations */
void Error(const char *str, ...);
void pprint(_LSPMessage& msg);


#endif
