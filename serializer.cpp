#include "serializer.h"

LSP_Packet Serializer::unmarshal(uint8_t* bytes, int msg_len)
{
	LSPMessage *msg;

	// Unpack the message using protobuf-c.
	msg = lspmessage__unpack(NULL, msg_len, bytes);
	if (msg == NULL)
	{
		fprintf(stderr, "Serializer::Error unpacking incoming message\n");
		throw "Serializer::Unmarshal Error!";
	}

	LSP_Packet packet = convert_from(msg);

	// Free the unpacked message
	lspmessage__free_unpacked(msg, NULL);

	return packet;
}

LSP_Packet Serializer::convert_from(LSPMessage* msg)
{
	LSP_Packet packet(
			msg->connid,
			msg->seqnum,
			msg->payload.len,
			msg->payload.data);

	return packet;
}

int Serializer::marshal(LSP_Packet packet, uint8_t* &buf)
{
	LSPMessage msg = LSPMESSAGE__INIT;

	msg.connid = packet.getConnId();
	msg.seqnum = packet.getSeqNo();
	msg.payload.len = packet.getLen();

	msg.payload.data = new uint8_t[msg.payload.len];
	memcpy(msg.payload.data, packet.getBytes(), msg.payload.len);

	int len = -1;

	len = lspmessage__get_packed_size (&msg); // This is the calculated packing length
	buf = (uint8_t*) malloc(len);             // Allocate memory
	lspmessage__pack (&msg, buf);             // Pack msg, including submessages

	/* Debug Code! Do not remove! */
//	packet.print();
//	pprint(msg);
//	fprintf(stderr,"Buffer [%d bytes]: ", len); // See the length of message
//	fwrite (buf, len, 1, stdout);           // Write to stdout to allow direct command line piping
//	printf("\n");
//
//	LSP_Packet packet2 = unmarshal(buf, len);
//	packet2.print();

	delete msg.payload.data;

	return len;
}
