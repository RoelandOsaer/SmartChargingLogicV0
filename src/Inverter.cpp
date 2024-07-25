#include "Inverter.h"
//default constructor
Inverter::Inverter()
{
	this->current = 0;
	this->voltage = 0;
	this->id = 0;
	this->inverter_active = false;
}
//normal constructor
Inverter::Inverter(int vol, int cur, int id)
{
	this->voltage = vol;
	this->current = cur;
	this->id = id;
	this->inverter_active = false;
}
//coppy constructor
Inverter::Inverter(const Inverter &inv) : voltage(inv.voltage), current(inv.current), id(inv.id), inverter_active(inv.inverter_active){
}
//move constructor
Inverter::Inverter(Inverter&& inv) noexcept : voltage(inv.voltage), current(inv.current), id(inv.id), inverter_active(inv.inverter_active) {
	inv.voltage = 0;
	inv.current = 0;
	inv.id = 0;
	inverter_active = false;
}
//copy assignment operator
Inverter& Inverter::operator=(const Inverter& inv) {
	if (this != &inv) {
		this->voltage = inv.voltage;
		this->current = inv.current;
		this->id = inv.id;
		this->inverter_active = inv.inverter_active;
	}
	return *this;
}
//move assignment operator
Inverter& Inverter::operator=(Inverter &&inv) noexcept{
	if (this != &inv) {
		this->voltage = inv.voltage;
		this->current = inv.current;
		this->id = inv.id;
		this->inverter_active = inv.inverter_active;
	
		inv.voltage = 0;
		inv.current = 0;
		inv.id = 0;
	}
	return *this;
}
//destructor
Inverter::~Inverter()
{
}
//Gets the inverter's voltage and current statistics
std::tuple<int, int> Inverter::get_inverter_stats(){
	return std::make_tuple(this->voltage,this->current);
}
//Starts the inverter
void Inverter::start_inverter(){
	//needs communication with intern hardware to turn on inverter.
	//this code will come here
	inverter_active = true;
}

void Inverter::stop_inverter(){
	//needs communication with intern hardware to turn off inverter
	//this code will come here
	inverter_active = false;
}
