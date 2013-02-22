#include "lsppacket.h"

//	LSP_Packet(): conn_id(-1), seq_no(-1)
//	{
//
//	}

LSP_Packet::LSP_Packet(int conn_id, int seq_no, size_t len, uint8_t* bytes)
	: conn_id(conn_id), seq_no(seq_no), len(len),
	  type(UNKNOWN), dataType(NOTKNOWN)
{
	memset(this->hostname, 0, INET_ADDRSTRLEN);;
	port = -1;

	stamp_msg_type();
	if(len <= 0)
		this->bytes = NULL;
	else
	{
		this->bytes = new uint8_t[len];
		memcpy(this->bytes, bytes, len);
		stamp_data_type();
	}
}

LSP_Packet::LSP_Packet(const LSP_Packet& that)
: conn_id(that.conn_id), seq_no(that.seq_no),
  len(that.len), type(that.type), dataType(that.dataType), port(that.port)
{
	if(len <= 0)
		this->bytes = NULL;
	else
	{
		this->bytes = new uint8_t[len];
		memcpy(this->bytes, that.bytes, len);
	}

	if(that.hostname != NULL)
		strcpy(this->hostname, that.hostname);
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

void LSP_Packet::stamp_msg_type()
{
	if(getConnId() == 0 && getSeqNo() == 0 &&
			getLen() == 0)
	{
		setType(CONN_REQ);
	}
	else if(getConnId() != 0 && getLen() == 0)
	{
		setType(ACK);
	}
	else if(getConnId() != 0 && getSeqNo() != 0 &&
			getLen() != 0)
	{
		setType(DATA);
	}
	else
	{
		fprintf( stderr, "MessageProcessor:: Unknown Packet Type!\n");
		//print();
	}
}

void LSP_Packet::stamp_data_type()
{
	uint8_t* bytes = getBytes();
	if(bytes[0] == 'j')
		setDataType(JOINREQUEST);
	else if(bytes[0] == 'c')
		setDataType(CRACKREQUEST);
	else if(bytes[0] == 'f')
		setDataType(FOUND);
	else if (bytes[0] == 'x')
		setDataType(NOTFOUND);
	else if (bytes[0] == 'a')
		setDataType(ALIVE);
	else
		setDataType(NOTKNOWN);
}

void LSP_Packet::setHostNameAndPort(char* const hostname, const int port)
{
	strcpy(this->hostname, hostname);
	this->port = port;
}

void LSP_Packet::print()
{
	printf("LSP_Packet::conn_id: %d seq_no: %d ", conn_id, seq_no);

	switch(type)
	{
	case CONN_REQ: printf("MsgType: CONN_REQ"); break;
	case ACK: printf("MsgType: ACK"); break;
	case DATA: break;
	default:
		printBytes(bytes, len);
		return;
	}
	printf(" ");

	switch(dataType)
	{
	case JOINREQUEST: printf("DataType: JOINREQUEST"); break;
	case CRACKREQUEST: printf("DataType: CRACKREQUEST");
		printf(" len: %u Data: %s", len, bytes);
		break;
	case FOUND: printf("DataType: FOUND");
		printf(" len: %u Data: %s", len, bytes);
		break;
	case NOTFOUND: printf("DataType: NOTFOUND"); break;
	case ALIVE: printf("DataType: ALIVE"); break;
	}
	printf("\n");
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

DataType LSP_Packet::getDataType() const {

	return dataType;
}


const char* LSP_Packet::getHostname() const {
	return hostname;
}

int LSP_Packet::getPort() const {
	return port;
}

void LSP_Packet::setDataType(DataType dataType) {
	this->dataType = dataType;
}

void LSP_Packet::setType(MessageType type) {
	this->type = type;
}
