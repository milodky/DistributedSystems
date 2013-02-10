
#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "lsp.h"
#include "header.h"
#include "lspmessage.pb-c.h"

class Serializer : public Uncopyable
{
public:
	void unmarshall(char* ipv4, int port, char* bytes, int msg_len)
	{
		LSPMessage *msg;

		// Read packed message from standard-input.
		uint8_t buf[MAX_MSG_SIZE];
		size_t msg_len = read_buffer (MAX_MSG_SIZE, buf);

		// Unpack the message using protobuf-c.
		msg = amessage__unpack(NULL, msg_len, buf);
		if (msg == NULL)
		{
			fprintf(stderr, "Error unpacking incoming message\n");
			exit(1);
		}


	}

};


#endif
