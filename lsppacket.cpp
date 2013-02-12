#include "lsppacket.h"

//	LSP_Packet(): conn_id(-1), seq_no(-1)
//	{
//
//	}

LSP_Packet::LSP_Packet(int conn_id, int seq_no, size_t len, uint8_t* bytes)
: conn_id(conn_id), seq_no(seq_no),
  len(len), bytes(new uint8_t[len]), type(UNKNOWN)
{
	memcpy(this->bytes, bytes, len);
}

LSP_Packet::LSP_Packet(const LSP_Packet& that)
: conn_id(that.conn_id), seq_no(that.seq_no),
  len(that.len), bytes(new uint8_t[len]), type(that.type)
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

void LSP_Packet::setHostNameAndPort(char* const hostname, const int port)
{
	strcpy(this->hostname, hostname);
	this->port = port;
}

void LSP_Packet::print()
{
	printf("LSP_Packet{\nconn_id: %d, seq_no: %d, len: %u\n",
			conn_id, seq_no, len);
	printBytes(bytes, len);
	printf("}\n");
}

LSP_Packet::~LSP_Packet()
{
	if (bytes) delete bytes;
}

uint8_t* LSP_Packet::getBytes() const {
	return bytes;
}

int LSP_Packet::getConnId() const {
	return conn_id;
}

size_t LSP_Packet::getLen() const {
	return len;
}

int LSP_Packet::getSeqNo() const {
	return seq_no;
}

MessageType LSP_Packet::getType() const {
	return type;
}

void LSP_Packet::setType(MessageType type) {
	this->type = type;
}

const char* LSP_Packet::getHostname() const {
	return hostname;
}

int LSP_Packet::getPort() const {
	return port;
}
