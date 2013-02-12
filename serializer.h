
#ifndef SERIALIZER_H
#define SERIALIZER_H

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
	LSP_Packet unmarshal(uint8_t* bytes, int msg_len);

	LSP_Packet convert_from(LSPMessage* msg);

	int marshal(LSP_Packet packet, uint8_t* &buf);
};


#endif
