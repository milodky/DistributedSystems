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

#pragma GCC diagnostic ignored "-Wwrite-strings"

#define LOCALHOST "localhost"
#define DEFAULT_HOST LOCALHOST
#define DEFAULT_PORT 5000
#define DEFAULT_PORT_C_STR "5000"

#define SERVER_ADDR LOCALHOST
#define SERVER_PORT "5000"

const int BAD_SOCKFD = -1;

#define SUCCESS 0
#define FAILURE 1

#endif
