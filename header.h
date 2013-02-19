#pragma once
#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <map>
#include <vector>
#include <math.h>
using namespace std;

#pragma GCC diagnostic ignored "-Wwrite-strings"

const int BAD_SOCKFD = -1;

#define SUCCESS 0
#define FAILURE 1
#define COMPLETE 2

#define MAX_MSG_SIZE 1024

// Global Parameters. For both server and clients.

#define _EPOCH_LTH 2.0
#define _EPOCH_CNT 5
#define _DROP_RATE 0.0

void printBytes(uint8_t* data, size_t len);

/* Class Declarations */
struct _LSPMessage;

class LSP;
class LSP_Server;
class LSP_Client;
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
class Epoch;
class EpochServer;
class EpochClient;

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
