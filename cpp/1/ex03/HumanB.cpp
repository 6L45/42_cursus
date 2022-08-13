#include "HumanB.hpp"

HumanB::HumanB(std::string name)
{
	this->_name = name;
	this->_weapon = NULL;
}

HumanB::~HumanB()
{
	std::cout << "thanks to his " << this->_weapon->getType() << " " << this->_name
	<< " was capable to survive one more day this apocalypse." << std::endl;
}

void	HumanB::attack()
{
	if (this->_weapon == NULL)
		std::cout << this->_name << " " << "unarmed but still, to the bitter end, with fists and teeth!" << std::endl;
	else
		std::cout << this->_name << " " << "attack with " << this->_weapon->getType() << std::endl;
}

void	HumanB::setWeapon(Weapon &weapon)
{
	std::cout << "weapon found : " << weapon.getType() << std::endl;
	this->_weapon = &weapon;
}