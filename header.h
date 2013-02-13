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
#include <openssl/sha.h>

using namespace std;

#pragma GCC diagnostic ignored "-Wwrite-strings"

//#define LOCALHOST "localhost"

//#define SERVER_ADDR LOCALHOST
//#define SERVER_PORT "5000"

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
class MessageProcessor;
class RequestMessageProcessor;
class ServerMessageProcessor;
class WorkerMessageProcessor;
class ConnInfo;
class MessageSender;
class LSP_Packet;

class Uncopyable
{
private:
	Uncopyable(const Uncopyable& that); // Disallow Copy Constructor
	Uncopyable& operator=(const Uncopyable&); // Disallow assignment operator

public:
	Uncopyable() {}
};

/* Function Declarations */
void Error(const char *str, ...);
void pprint(_LSPMessage& msg);


#endif
