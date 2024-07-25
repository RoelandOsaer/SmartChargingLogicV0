#include "EvseController.h"
#include "AuthenticationManager.h"
#include <iostream>

//for demo use only
#define CAR_CONNECTED true

//default constructor
EvseController::EvseController()
{
	this->auth_manager = new AuthenticationManager();
	this->session_manager = new ChargingSessionManager();

	this->offline_preference = UserPreferences();
	this->used_preference = UserPreferences();

	this->current_state = SetupState::Idle;
	this->start_state_of_charge = 0;
	this->stop_state_of_charge = 0;
	this->car_is_charging = false;
	this->msg_for_user = "";
	this->availabe_solar_enegie = true;
	this->running_ = false;
}

//destructor
EvseController::~EvseController()
{
	delete auth_manager;
	delete session_manager;
}

//starting periodic communication with the car
void EvseController::start_periodic_comm_with_car() {
	running_ = true;
	periodic_thread_ = std::thread(&EvseController::periodic_comm_with_car, this);
}

//stopping periodic communication with the car
void EvseController::stop_periodic_comm_with_car() {
	running_ = false;
	if (periodic_thread_.joinable()) {
		periodic_thread_.join();
	}
}

//This function will be called when start_periodic_comm_with_car is done
void EvseController::periodic_comm_with_car() {
	while (running_) {
		std::this_thread::sleep_for(std::chrono::seconds(10));

		//check the EV state every 10 sec
		checking_ev_state();
		//sending the information that is gaderd during the checking_ev_state function
		//and sends it back to the user via MQQT
		send_message_to_user("ev_state", msg_for_user);
	}
}

//This function does al the initialisation to setup a charing session
void EvseController::start_charging_session()
{
	//checking if the car is not charging already
	if (!car_is_charging) {

	
		msg_for_user = "";
		msg_for_user +=  "Checking cable connection\n";


	/* 
		- A state machine is build to handle the initiali
		- The initialization pocess is brokin down into several states and events. Each state transision is handled by a corresponding function
		- Lambde functions are used to pass a state handling function to the 'process_event' method.
			- The use of the Lambda function is to prevent repetition and icreasing the flexility for further expansion of the code.
		- The 'process_event' method ensures that the current state allows the transition and then executes the provided function to handle the event.

		- Maybe in this state, a state machine is a bit overkill. But can be easy to expand when there are more posible ways to initialize.
	*/
		//checking if a car is connected to the charger
		if (!process_event([this](SetupEvent event, SetupState& state) { handle_idle_state(event, state); }, SetupEvent::checking_car_connection, current_state)) {
			return;
		}

		// Initial communication for knowing the required voltage, current, and session_id
		if (!process_event([this](SetupEvent event, SetupState& state) { handle_car_connected_state(event, state); }, SetupEvent::start_initial_comm_with_car, current_state)) {
			return;
		}

		// Choose an inverter based on the voltage and current
		if (!process_event([this](SetupEvent event, SetupState& state) { handle_initial_comm_done_state(event, state); }, SetupEvent::chosing_inverter, current_state)) {
			return;
		}

		// Authenticate with RFID, QR, or payment station
		if (!process_event([this](SetupEvent event, SetupState& state) { handle_inverter_chosen_state(event, state); }, SetupEvent::start_authentication, current_state)) {
			return;
		}
		//	stop state machine


		//start the Inverter
		session_manager->start_inverter();
	
		//Do a standard communication with the EV to see if car is realy charging.
		car_is_charging = session_manager->do_charging_comm_with_car();
		if (car_is_charging) {
			//save the state of charge to calculate total charging after session
			start_state_of_charge = session_manager->get_state_of_charge();
			msg_for_user += "The car has started charging\n\n";

			//start the periodic communication with the car so the user can get up to date data from the car.
			start_periodic_comm_with_car();
		}
		// if the car is not charing after starting the inverter stop the charging session
		else {
			msg_for_user += "The car is not charging. Clossing session\nTry again later.\n";
			stop_charging_session();
		}
	}
	// if the car is already charging: do nothing.
	else {
		msg_for_user += "The car is already charging: No action done.";
	}

}

// Processes an event in the state machine
template <typename Func>
bool EvseController::process_event(Func func, SetupEvent event, SetupState& current_state)
{
	if (current_state != SetupState::no_charging_possible) {
		func(event, current_state);
		return true;
	}
	else {
		std::cout << "Error: Abort session.\n";
		return false;
	}
	return false;
}

//Handles the idle state in the state machine
void EvseController::handle_idle_state(SetupEvent event, SetupState& current_state) {
	switch (event)
	{
	case SetupEvent::checking_car_connection:
		if (CAR_CONNECTED) {
			msg_for_user += "A car is connected\n";
			msg_for_user += "Setting up Charging Session\n\n";
			current_state = SetupState::car_connected;
			break;
		}
		else {
			current_state = SetupState::no_charging_possible;
			msg_for_user += "No Car connected.\n\n";
			break;
		}
	case SetupEvent::start_initial_comm_with_car:
	case SetupEvent::chosing_inverter:
	case SetupEvent::start_authentication:
	default:
		current_state = SetupState::no_charging_possible;
		msg_for_user += "abort Session.\n";
		break;
	}
}

//Handles the car connected state in the state machine
void EvseController::handle_car_connected_state(SetupEvent event, SetupState& current_state)
{
	switch (event)
	{
	case SetupEvent::start_initial_comm_with_car:
		msg_for_user += "doing the initial communication with the car\n";
		if (session_manager->do_initial_comm_with_car()) {
			current_state = SetupState::initial_comm_done;
			break;
		}
		else {
			msg_for_user += "inititial communication with the car faild.\n\n";
			current_state = SetupState::no_charging_possible;
			break;
		}
	case SetupEvent::checking_car_connection:
	case SetupEvent::chosing_inverter:
	case SetupEvent::start_authentication:
	default:
		current_state = SetupState::no_charging_possible;
		msg_for_user += "Abort session\n";
		break;
	}
}

//Handles the initial communication done state in the state machine.
void EvseController::handle_initial_comm_done_state(SetupEvent event, SetupState& current_state)
{
	switch (event)
	{
	case SetupEvent::chosing_inverter:
		msg_for_user += "chosing a usable inverter\n";
		if (session_manager->chose_inverter()) {
			msg_for_user += "An usable inverter is found\n\n";
			current_state = SetupState::inverter_chosen;
			break;
		}
		else {
			current_state = SetupState::no_charging_possible;
			msg_for_user += "No usable inverters are found.\n\n";
			break;
		}
		
	case SetupEvent::checking_car_connection:
	case SetupEvent::start_initial_comm_with_car:
	case SetupEvent::start_authentication:
	default:
		current_state = SetupState::no_charging_possible;
		std::cout << "Abort session.\n";
		break;
	}
}

//Handles the inverter chosen state in the state machine.
void EvseController::handle_inverter_chosen_state(SetupEvent event, SetupState& current_state)
{
	switch (event)
	{
	case SetupEvent::start_authentication:

		msg_for_user += "Start Authentication with RFID, QR-code or payment station.\n";
		if (handle_authentication("1234abc")) {
			msg_for_user += "authentication Done\n\n";
		}
		else {
			current_state = SetupState::no_charging_possible;
			msg_for_user += "authentication NOK\n\n";
			break;
		} 
		current_state = SetupState::authenticated;
		break;
	case SetupEvent::checking_car_connection:
	case SetupEvent::start_initial_comm_with_car:
	case SetupEvent::chosing_inverter:
	default:
		current_state = SetupState::no_charging_possible;
		msg_for_user += "Abort session.\n";
		break;
	}
}

//Checks the state of the electric vehicle.
void EvseController::checking_ev_state()
{
	//do a normal comm with the ev to check if the ev is still charging
	car_is_charging = session_manager->do_charging_comm_with_car();

	if (car_is_charging) {

		//check if the car needs to be charged by checking the schedule.
		if (!is_within_time_window(used_preference.get_schedule())) {
			msg_for_user += "The car will stop charging: time out of preset schedule.";
			stop_charging_session();
		}

		//Always charge the car if ther is solar energy available.
		if (availabe_solar_enegie) {
			msg_for_user += "The car is charging on solar.\n\n";
		}
		else {
			//there is no solar energie available but percentage of grit usage is not exceded => charging
			if (get_car_charged_on_grid() < 100 - used_preference.get_solar_usage()) {
				msg_for_user += "The car is charging on the grid.\n\n";
			}
			//there is no solar energie available and percentage of grid usage is exceded => pauzing charging
			else if (get_car_charged_with_solar() < used_preference.get_solar_usage()) {
				msg_for_user += "There is no solar energie available: pauzing session.\n";
				pauze_charging_session();
			}
			//if the two values are exceded the car must be fully loaded => stop charging.
			else if (get_car_charged_with_solar() >= used_preference.get_solar_usage() &&
					get_car_charged_on_grid() >= 100 - used_preference.get_solar_usage()) {
				msg_for_user += "The Car must be fully loaded: stop charing session\n";
				stop_charging_session();
			}
		}
	}
	//if the evse lost connection the car is not charging anymore, the session will be stopped
	else {
		msg_for_user += "The car has lost connection and is not charging.\n";
		msg_for_user += "Ending session.\n";
		stop_charging_session();
	}
}

// stopping the charging session
void EvseController::stop_charging_session()
{
	//checking if the car is charging before the car needs to stop charging
	if (car_is_charging) {
		//stop the inverter
		msg_for_user += "Stopping the charging session.\n";
		session_manager->stop_inverter();
		msg_for_user += "inverter stopped.\n";
		//stop payment session
		auth_manager->deauthenticate();
		msg_for_user += "payment stopped\n";
		//calculation the total amount of charge added to the care
		msg_for_user += "Calculate total charge to car:\n";
		stop_state_of_charge = session_manager->get_state_of_charge();
		msg_for_user += "The car has charged: ";
		msg_for_user += std::to_string(stop_state_of_charge - start_state_of_charge);
		msg_for_user += "%.\n\n";
		car_is_charging = false;
		delete session_manager;
		delete auth_manager;
	}
	//if the car is allready stopped charging: do notting
	else {
		msg_for_user += "car has already stopped charging.\n";
	}
}

//pauzing the charing of the car.
void EvseController::pauze_charging_session()
{
	//check ik the car is charging
	if (car_is_charging) {
		//stop the inverter
		msg_for_user += "Stopping the charging session.\n";
		session_manager->stop_inverter();
		msg_for_user += "inverter stopped.\n";
		//calculation the total amount of charge added to the care
		msg_for_user += "Calculate total charge to car:\n";
		stop_state_of_charge = session_manager->get_state_of_charge();
		msg_for_user += "The car has charged: ";
		msg_for_user += std::to_string(stop_state_of_charge - start_state_of_charge);
		msg_for_user += "%.\n\n";
		car_is_charging = false;
		msg_for_user += "car has pauzed charging.\n";
	}
	//if the car was not charging: do nothing.
	else {
		msg_for_user += "car was not charging: pauzing not necassery.\n";
	}
}
//Handles payment authentication with the provided key.
bool EvseController::handle_authentication(std::string key)
{
	return auth_manager->authenticate(key);
}

//Updating the user preferences to the new user preferences.
void EvseController::update_user_preferences(const UserPreferences& preference)
{
	this->used_preference = preference;
	std::cout << "The user preference has been updated.\n\n";
}

//Callback function for receiving MQQT messages from the user.
void EvseController::on_MQTT_message(const std::string& topic, const std::string& message) {
	
	std::cout << "Received message on topic " << topic
		<< ": " << message << std::endl;
	// Add your logic here
	if (topic == "update_pref"){
		used_preference.set_schedule_with_string(message);
		msg_for_user = "";
	}
	if (topic == "start_charg_ses") {
		start_charging_session();
		send_message_to_user("charg_ses", msg_for_user);
		msg_for_user = "";
	}
	if (topic == "check_ev_state") {
		checking_ev_state();
		send_message_to_user("ev_state", msg_for_user);
		msg_for_user = "";
	}
	if (topic == "stop_charg_ses") {
		stop_charging_session();
		send_message_to_user("charg_ses", msg_for_user);
		msg_for_user = "";
	}
}
//Sets the callback function for outgoing MQTT messages to the user
void EvseController::set_message_callback(std::function<void(const std::string&, const std::string&)> callback)
{
	send_message_callback_ = callback;
}

//sends a message to the user via the callback function in the MQTT class
void EvseController::send_message_to_user(const std::string& topic, const std::string& message)
{
	send_message_callback_(topic, message);
}

//Checks if the current time is within the specified schedule
bool EvseController::is_within_time_window(const std::string& schedule)
{
	
	//for demo purpose return true
	return true;
}

//Checks how much percentage the car has charge on solar
int EvseController::get_car_charged_with_solar()
{
	
	//for demo purpose return 40
	return 40;
}

//Checks how much percentage the car has charge on the grid
int EvseController::get_car_charged_on_grid()
{
	//for demo purpose return 40
	return 20;
} 
