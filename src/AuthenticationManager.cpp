#include "AuthenticationManager.h"
#include <string>
#define  CLOUD_KEY "1234abc"

//default constructor
AuthenticationManager::AuthenticationManager()
{
	this->active = false; 
}

//destructor
AuthenticationManager::~AuthenticationManager()
{
}
//Authenticates the payment session with a given key
bool AuthenticationManager::authenticate(std::string key)
{
	// all the communication with RFID, QR code or payment station is done here
	// dummy code with key is used here
	this->active = (key == CLOUD_KEY);
	return this->active;
}
//Checks if the payment session is authenticated
bool AuthenticationManager::is_authenticated()
{
	return this->active;
}
//Deauthenticates the session
void AuthenticationManager::deauthenticate()
{
	this->active = false;
}
