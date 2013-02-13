#include "connectionInfo.h"

ConnInfo::ConnInfo(int connId, int p, const char* const host) : connectionID(connId), port(p)
{
	/* Copy Hostname */
	strcpy(this->hostName, host);

	//default values when constructed.
	msgSent = false; //Only now connection request has come in. So msgSent will be false.
	isAlive = true;  //Assumed alive since connection request has just come in.

	//change these based on client and server
//	countMsgsRcd = 1; //only connection request is got at this point.

	seq_no = 0;
	epochsSinceMsgRcd = 0;
	epochsSinceMsgSent = 0;
}

void ConnInfo::add_to_outMsgs(LSP_Packet packet)
{
	outMsgs.push(packet);
}

bool ConnInfo::isMsgToBeSent()
{
	if(isAlive && !msgSent && outMsgs.size()!=0)
		return true;
	return false;
}

int ConnInfo::getOutMsgsCount() const
{
	return outMsgs.size();
}
