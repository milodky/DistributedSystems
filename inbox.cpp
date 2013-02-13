#include "inbox.h"

Inbox::Inbox()
{
	pthread_mutex_init(&mutex_inbox, NULL);
}

bool Inbox::isEmpty()
{
	return inbox.size() == 0;
}

void Inbox::add_msg(LSP_Packet packet)
{
	/* Lock before modifying! */
	pthread_mutex_lock (&mutex_inbox);

	fprintf(stderr, "Inbox: Adding packet:\n");
	packet.print();
	inbox.push(packet);

	/* Unlock after modifying! */
	pthread_mutex_unlock (&mutex_inbox);
}

LSP_Packet Inbox::pop_msg()
{
	/* Lock before modifying! */
	pthread_mutex_lock (&mutex_inbox);

	fprintf(stderr, "Inbox: Popping packet:\n");
	LSP_Packet packet = inbox.front();
	inbox.pop();
	/* Unlock after modifying! */
	pthread_mutex_unlock (&mutex_inbox);
	return packet;
}

Inbox::~Inbox()
{
	pthread_mutex_destroy(&mutex_inbox);
}
