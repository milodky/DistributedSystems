#include "connectionInfo.h"

ConnInfo::ConnInfo(int connId, int p, const char* const host) : connectionID(connId), port(p)
{
	/* Copy Hostname */
	strcpy(this->hostName, host);

	//default values when constructed.
	msgSent = false; //Only now connection request has come in. So msgSent will be false.
	isAlive = true;  //Assumed alive since connection request has just come in.
	isWorker = false;
	//change these based on client and server
	//	countMsgsRcd = 1; //only connection request is got at this point.

	seq_no = 0;
	resetEpochCount();
	updateTimestamp();

	pthread_mutex_init(&mutex_outbox, NULL);
}

void ConnInfo::add_to_outMsgs(LSP_Packet packet)
{
	if(getOutMsgsCount() > 0)
		if(get_front_msg().getType() == ACK)
			pop_outMsgs();

	/* Lock before modifying! */
	pthread_mutex_lock (&mutex_outbox);

	/* This has to hold all the time. The sent packet should always have
	 * the same connection ID as the connection info object.
	 * During, connection initiation both have the value 0 */
	assert (getConnectionId() == packet.getConnId());

//	fprintf(stderr, "ConnInfo::outbox size is :%u\n", outMsgs.size());
//	fprintf(stderr, "ConnInfo::Adding packet to conn_id:%d Outbox:\n", connectionID);
//	packet.print();
	outMsgs.push(packet);

	/* Unlock after modifying! */
	pthread_mutex_unlock (&mutex_outbox);
}

LSP_Packet ConnInfo::get_front_msg() const
{
	return outMsgs.front();
}

void ConnInfo::pop_outMsgs()
{
	/* Lock before modifying! */
	pthread_mutex_lock (&mutex_outbox);

	fprintf(stderr, "ConnInfo::Popping packet to conn_id:%d Outbox:\n", connectionID);
	assert (!outMsgs.empty());
	outMsgs.pop();
	msgSent = false;

	/* Unlock after modifying! */
	pthread_mutex_unlock (&mutex_outbox);
}

bool ConnInfo::isMsgToBeSent() const
{
	if(isAlive && !msgSent && outMsgs.size()!=0)
		return true;
	return false;
}

int ConnInfo::getOutMsgsCount() const
{
	return outMsgs.size();
}

int ConnInfo::popClients() {
	assert (!clients.empty());
	int c = clients.front();
	clients.pop();
	return c;
}

void ConnInfo::pushClients(int client) {
	this->clients.push(client);
}

int ConnInfo::getClientsCount() const {
	this->clients.size();
}

int ConnInfo::getConnectionId() const {
	return connectionID;
}

void ConnInfo::setConnectionId(int connectionId) {
	connectionID = connectionId;
}

char* ConnInfo::getHash() const {
	return hash;
}

void ConnInfo::setHash(char* hash) {
	this->hash = hash;
}

const char* ConnInfo::getHostName() const {
	return hostName;
}

bool ConnInfo::isIsAlive() const {
	return isAlive;
}

void ConnInfo::setIsAlive(bool isAlive) {
	this->isAlive = isAlive;
}

bool ConnInfo::isIsWorker() const {
	return isWorker;
}

void ConnInfo::setIsWorker(bool isWorker) {
	this->isWorker = isWorker;
}

int ConnInfo::getLen() const {
	return len;
}

void ConnInfo::setLen(int len) {
	this->len = len;
}

bool ConnInfo::isMsgSent() const {
	return msgSent;
}

void ConnInfo::setMsgSent(bool msgSent) {
	this->msgSent = msgSent;
}

int ConnInfo::getPort() const {
	return port;
}

void ConnInfo::setPort(int port) {
	this->port = port;
}

int ConnInfo::getSeqNo() const {
	return seq_no;
}

void ConnInfo::incrementSeqNo() {
	seq_no = seq_no + 1;
}

clock_t ConnInfo::getTimestamp() const {
	return timestamp;
}

void ConnInfo::updateTimestamp()
{
	this->timestamp = clock();
}

void ConnInfo::incrementEpochCount()
{
	epoch_count++;
}

void ConnInfo::resetEpochCount()
{
	epoch_count = 0;
}

unsigned ConnInfo::getEpochCount() const
{
	return epoch_count;
}

ConnInfo::~ConnInfo()
{
	pthread_mutex_destroy(&mutex_outbox);
}
