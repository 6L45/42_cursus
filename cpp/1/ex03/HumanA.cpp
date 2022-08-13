#include "HumanA.hpp"

HumanA::~HumanA()
{
	std::cout << "thank to his " << this->_weapon.getType() << " " << this->_name
	<< " was capable to survive one more day this apocalypse." << std::endl;
}

void	HumanA::attack()
{
	std::cout << this->_name << " " << "attack with " << this->_weapon.getType() << std::endl;
}
