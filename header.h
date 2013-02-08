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

/* Class Declarations */
class LSP;

/* Function Declarations */
void Error(const char *str, ...);

#endif
