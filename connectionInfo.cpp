#include "connectionInfo.h"


void ConnInfo::addPacket(int seqNo, size_t len, uint8_t *bytes)
	{
		//Gets the message, marshals it with relevant info and pushes to queue.
		LSP_Packet packet(connectionID, seqNo, len, bytes);
		outMsgs.push(packet);
	}

