#include "zombie.hpp"

Zombie::Zombie(std::string name)
{
	this->_name = name;
}

Zombie::~Zombie(void)
{
	std::cout << this->_name << " is dead... dead!(again but for good this time)" NL;
}

void	Zombie::announce(void) const
{
	std::cout << this->_name << " BraiiiiiiinnnzzzZ..." NL;
}

void	Zombie::assign_name(std::string name)
{
	this->_name = name;
}
