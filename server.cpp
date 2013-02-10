#include "lsp.h"
#include "serializer.h"

void connect()
{
	LSP_Server server;
	server.init();
}

int main ()
{
//	connect();
	uint8_t bytes[40];
	LSP_Packet packet(5, 5, 4, bytes);
	Serializer serializer;
	serializer.marshal(packet);
	return 0;
}
