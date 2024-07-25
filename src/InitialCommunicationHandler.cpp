#include "InitialCommunicationHandler.h"

//Default Constructor
InitialCommunicationHandler::InitialCommunicationHandler()
{
	required_current = 0;
	required_voltage = 0;
}

//Destructor
InitialCommunicationHandler::~InitialCommunicationHandler()
{
}

//Gets the required voltage and current from the car.
std::tuple<int,int> InitialCommunicationHandler::get_initial_information_from_car()
{	

	// This is for demo purpose only. Other logic needed to do effectice communication over PLC to the car.
	// Getting a id from EV for further communication
	this->session_id = 245;

	//dummy data 400V 40A
	this->required_current = 10;
	this->required_voltage = 400;
	
	return std::make_tuple(required_voltage, required_current);
}



