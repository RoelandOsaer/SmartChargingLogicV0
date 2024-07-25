#include "CommunicationHandler.h"

//Default constructor
CommunicationHandler::CommunicationHandler()
{
	//communicate with EV to get id
	this->session_id = NULL;
	this->last_msg_send = false;
}

//Destructor
CommunicationHandler::~CommunicationHandler()
{
}

//Gets the session ID
int CommunicationHandler::get_session_id()
{
	return this->session_id;
}

//Sets the session ID
void CommunicationHandler::set_session_id(int session_id)
{
	this->session_id = session_id;
}

//Checks if the last message was sent, if not? In this demo we assume that the care has lost connection and is no longer charging.
bool CommunicationHandler::is_last_msg_send()
{
	return last_msg_send;
}
