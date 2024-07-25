#include "ChargingSessionCommunicationHandler.h"

//default constructor
ChargingSessionCommunicationHandler::ChargingSessionCommunicationHandler()
{
	state_of_charge = 0;
	battery_temp = 0;
}

//destructor
ChargingSessionCommunicationHandler::~ChargingSessionCommunicationHandler()
{
}
//Updates the state of charge and battery temperature from the car.
void ChargingSessionCommunicationHandler::update_stats_from_car()
{
	//Communicate with EV via PLC and updates statistics
	//To communicate the session_id is needed.
	state_of_charge = 76;
	battery_temp = 35;
	//when communication failed aka the car is not charing: last_msg_send=false
	//for demo purpose communication never fails.
	last_msg_send = true;
}
//Gets the state of charge and battery temperature.
std::tuple<int, int> ChargingSessionCommunicationHandler::get_stats()
{
	return std::make_tuple(state_of_charge,battery_temp);
}

