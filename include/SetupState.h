#pragma once
#include <map>

enum class SetupState {
	Idle,
	car_connected,
	initial_comm_done,
	inverter_chosen,
	authenticated,
	no_charging_possible
};

enum class SetupEvent {
	checking_car_connection,
	start_initial_comm_with_car,
	chosing_inverter,
	start_authentication,
};