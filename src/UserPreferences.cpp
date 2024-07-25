#include "UserPreferences.h"
#include <iostream>

//defautl constructor
UserPreferences::UserPreferences()
{
	solar_usage = 0;
	schedule = "09:00-22:00";
}

//normal constructor
UserPreferences::UserPreferences(int solar_usage, const std::string& schedule)
{
	set_solar_usage(solar_usage);
	set_schedule(schedule);	
}

//destructor
UserPreferences::~UserPreferences()
{
}
//Copy constructor.
UserPreferences::UserPreferences(const UserPreferences& prefernece):solar_usage(prefernece.solar_usage),schedule(prefernece.schedule)
{
}
//Gets the percentage of solar energy usage
int UserPreferences::get_solar_usage() const
{
	return solar_usage;
}
//Gets the schedule for solar energy usage.
std::string UserPreferences::get_schedule() const
{
	return schedule;
}
//Sets the percentage of solar energy usage
void UserPreferences::set_solar_usage(int solar_usage)
{
	if (is_valid_solar_usage_percentage(solar_usage)) {
		this->solar_usage = solar_usage;
	}
	else {
		std::cerr << "Invalid value for solar_usage. Setting it to 0.";
		this->solar_usage = 0;
	}
}
//Sets the schedule for solar energy usage.
void UserPreferences::set_schedule(const std::string& schedule)
{
	if (is_valid_schedule(schedule)) {
		this->schedule = schedule;
	}
	else {
		std::cerr << "Invalid value for schedule. Setting it to 09:00-22:00";
		this->schedule = "09:00-22:00";
	}
}


//Checks if the given solar usage percentage is valid.
bool UserPreferences::is_valid_solar_usage_percentage(int percentage) const {
	return percentage >= 0 && percentage <= 100;
}
//Checks if the given schedule is valid.
bool UserPreferences::is_valid_schedule(const std::string& schedule) const {
	
	if (schedule.empty() || schedule.size() != 11 || schedule[2] != ':' || schedule[5] != '-' || schedule[8] != ':') {
		return false;
	}
	return true;	
}

//Sets the schedule based on a string input
void UserPreferences::set_schedule_with_string(const std::string& input) {

	//check if there is a new line character on the end of the string. ifso, delete it.
	std::string msg = "";
	if (input.size() >= 1 && input[input.size() - 1] == '\n') {
		msg =  input.substr(0, input.size() - 1);
	}
	else {
		msg = input;
	}

	size_t commaPos = msg.find(',');

	if (commaPos == std::string::npos) {
		throw std::invalid_argument("Input string does not contain a comma.");
	}

	std::string numberPart = msg.substr(0, commaPos);
	std::string timeRangePart = msg.substr(commaPos + 1);

	if (numberPart.empty() || timeRangePart.empty()) {
		throw std::invalid_argument("Input string is malformed.");
	}
	set_schedule(timeRangePart);

	int number;
	try {
		number = std::stoi(numberPart);
	}
	catch (const std::invalid_argument& e) {
		throw std::invalid_argument("Number part is not a valid integer.");
	}
	
	set_solar_usage(number);
	std::cout << "Preferenc has been set.";
}
