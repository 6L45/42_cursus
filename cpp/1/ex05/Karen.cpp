#include "Karen.hpp"

Karen::Karen()
{
	this->resp[0].alert_lvl = "DEBUG";
	this->resp[0].func = &Karen::debug;

	this->resp[1].alert_lvl = "INFO";
	this->resp[1].func = &Karen::info;
	
	this->resp[2].alert_lvl = "WARNING";
	this->resp[2].func = &Karen::warning;
	
	this->resp[3].alert_lvl = "ERROR";
	this->resp[3].func = &Karen::error;
}

Karen::~Karen()
{
	;
}

void Karen::debug(void)
{
	std::cout << "I love to get extra bacon for my 7XL-double-cheese-triple-pickle-special-ketchup burger. I just love it!" << std::endl;
}
void Karen::info(void)
{
	std::cout << "I cannot believe adding extra bacon cost more money. You don’t put enough! If you did I would not have to ask for it!" << std::endl;
}
void Karen::warning(void)
{
	std::cout << "I think I deserve to have some extra bacon for free. I’ve been coming here for years and you just started working here last month." << std::endl;
}
void Karen::error(void)
{
	std::cout << "This is unacceptable, I want to speak to the manager now." << std::endl;
}

void Karen::complain(std::string level)
{
	int	i = 0;

	while (i < 4 && level.compare(this->resp[i].alert_lvl))
		i++;
	if (i < 4)
		(this->*resp[i].func)();
}
