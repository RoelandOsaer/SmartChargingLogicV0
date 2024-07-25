#include "ChargingSessionManager.h"
#include "Inverter.h"
#include <tuple>
#include <iostream>
//Default constructor
ChargingSessionManager::ChargingSessionManager()
{
	this->voltage = 0;
	this->current = 0;
	this->session_id = 0;
	this->init_comm_handler = new InitialCommunicationHandler();
	this->used_inverter = nullptr;
	this->session_comm_handler = nullptr;
	this->used_preference = nullptr;
	this->first_comm_after_init = true;
}
//destructor
ChargingSessionManager::~ChargingSessionManager()
{
}
//Performs initial communication with the car
bool ChargingSessionManager::do_initial_comm_with_car()
{
	//for demo perpose: comm always works
	std::tie(voltage, current) = init_comm_handler->get_initial_information_from_car();
	session_id = init_comm_handler->get_session_id();
	std::cout << "Initial communication is done \n";
	std::cout << "The requierd voltage is: " << this->voltage << "V.\n";
	std::cout << "The requierd current is: " << this->current << "A.\n\n";

	return true;
}

//Performs communication with the car during the charging session.
bool ChargingSessionManager::do_charging_comm_with_car()
{
	// if its the first communication after init, initialize a new CharginSessionCommunicationsHandler objec.
	if (first_comm_after_init)
	{
		session_comm_handler = new ChargingSessionCommunicationHandler();
		session_comm_handler->set_session_id(init_comm_handler->get_session_id());
		first_comm_after_init = false;
		std::cout << "Initial state of the car\n";
	}
	// get the stats from the car and print this out.
	session_comm_handler->update_stats_from_car();
	std::cout << "State of the car.\n";
	std::cout << "state of charge: " << get<0>(session_comm_handler->get_stats()) << "%\n";
	std::cout << "battery temp: " << get<1>(session_comm_handler->get_stats()) << "°C\n";
	//checks if last message is send.
	return session_comm_handler->is_last_msg_send();
}

//choses a inverter
bool ChargingSessionManager::chose_inverter()
{
	if (voltage != 0 and current != 0) {
		//dummy inverters
		//normaly obtaind by the CAN bus.
		Inverter* inv0 = new Inverter(400, 10, 983);
		Inverter* inv1 = new Inverter(400, 20, 751);
		Inverter* inv2 = new Inverter(800, 10, 912);

		std::vector<Inverter*> inverters;
		inverters.push_back(inv0);
		inverters.push_back(inv1);
		inverters.push_back(inv2);

		//algoritme for choosing the correct inverter
		//for demo purpose using inverter 1
		used_inverter = std::move(inverters[1]);

		return true;
	}
	return false;
}
//Gets the voltage level for the charging session.
int ChargingSessionManager::get_voltage() const
{
	return this->voltage;
}

//Gets the current level for the charging session.
int ChargingSessionManager::get_current() const
{
	return this->current;
}

//Starts the inverter for the charging session.
void ChargingSessionManager::start_inverter()
{
	used_inverter->start_inverter();
}

//Stops the inverter for the charging session.
void ChargingSessionManager::stop_inverter()
{
	used_inverter->stop_inverter();
}

//Gets the state of charge of the car.
int ChargingSessionManager::get_state_of_charge()
{
	return get<0>(session_comm_handler->get_stats());
}