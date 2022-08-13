#include "zombie.hpp"

Zombie::Zombie(std::string name)
{
	this->_name = name;
	std::cout << this->_name << " is in da place now" NL;
}

Zombie::~Zombie(void)
{
	std::cout << this->_name << " is dead... dead!(again but for good this time)" NL;
}

void	Zombie::announce(void) const
{
	std::cout << this->_name << " BraiiiiiiinnnzzzZ..." NL;
}
