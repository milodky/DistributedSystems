#ifndef LSPPACKET_H
#define LSPPACKET_H

#include <netdb.h>

#include "header.h"

enum MessageType { UNKNOWN, CONN_REQ, DATA, ACK };
enum DataType { NOTKNOWN, JOINREQUEST, CRACKREQUEST, FOUND, NOTFOUND, ALIVE};

class LSP_Packet
{
private:
	int conn_id;
	int seq_no;

	size_t len;
	uint8_t* bytes;

	MessageType type;
	DataType dataType;

	/* Required for each packet since when receiving
	 * connection requests. we do not have a conn_id yet! */
	char hostname[INET_ADDRSTRLEN];
	int port;

	LSP_Packet& operator = (const LSP_Packet& that);

	void stamp_msg_type();
	void stamp_data_type();

	void setDataType(DataType dataType);
	void setType(MessageType type);
public:
//	LSP_Packet(): conn_id(-1), seq_no(-1);

	LSP_Packet(int conn_id, int seq_no, size_t len, uint8_t* bytes);
	LSP_Packet(const LSP_Packet& that);

	/* Please do not delete this code */
//	LSP_Packet& operator = (const LSP_Packet& that);

	void setHostNameAndPort(char* hostname, int port);
	void print();


	~LSP_Packet();

	uint8_t* getBytes() const;
	int getConnId() const;
	size_t getLen() const;
	int getSeqNo() const;
	MessageType getType() const;
	DataType getDataType() const;
	const char* getHostname() const;
	int getPort() const;

};

#endif
