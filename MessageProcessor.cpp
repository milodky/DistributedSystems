#include "MessageProcessor.h"

MessageProcessor::MessageProcessor(Inbox* in) : inbox(in)
{

}

int MessageProcessor::poll_inbox()
{
	while(true)
	{
		/* Empty Inbox: Life is chill! :-) */
		if(inbox->isEmpty()) continue;

		LSP_Packet packet = inbox->pop_msg();
		process_incoming_msg(packet);
	}
}

void MessageProcessor::process_incoming_msg(LSP_Packet packet)
{

}

MessageProcessor::~MessageProcessor()
{
	if(inbox) delete inbox;
}
