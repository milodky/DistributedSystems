
#ifndef SERIALIZER_H
#define SERIALIZER_H

#include "lsp.h"
#include "header.h"
#include "lspmessage.pb-c.h"

/**
typedef struct _ProtobufCBinaryData ProtobufCBinaryData;
struct _ProtobufCBinaryData
{
  size_t len;
  uint8_t *data;
};
 */

class Serializer : public Uncopyable
{

public:
	LSP_Packet* unmarshall(char* ipv4, int port, char* bytes, int msg_len)
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

		LSP_Packet* packet = convert_from(msg);

		// Free the unpacked message
		amessage__free_unpacked(msg, NULL);

		return packet;
	}

	LSP_Packet* convert_from(LSPMessage* msg)
	{
		LSP_Packet* packet = new LSP_Packet(
				msg->connid,
				msg->seqnum,
				msg->payload.len,
				msg->payload.data);

		return packet;
	}

};


#endif
