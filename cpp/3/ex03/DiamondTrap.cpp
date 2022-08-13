#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap(std::string name): ScavTrap(name), FragTrap(name), ClapTrap(name)
{
	this->_name = name;
	out "DiamondTrap unit on" nl;
	this->_hit_pts = 99;
	this->_hit_pts_modified = this->_hit_pts;
	this->_energy = 49;
	this->_attack_damage = 19;
}

DiamondTrap::~DiamondTrap()
{
	out "DiamondTrap off " nl;
}

void	DiamondTrap::whoAmI()
{
	out this->_name nl;
}

void 	DiamondTrap::attack(const std::string &target)
{
	if (!this->_alive)
	{
		already_dead();
		return ;
	}
	if (!this->_energy)
	{
		out "ClapTRap : DiamondTrap unit " << this->_name
		<< " doesn't have any power anymore, thus, can't do now, let him rest in peace" nl;
		return ;
	}
	this->_energy--;
	out "ClapTRap DiamondTrap unit " << this->_name << " attack " << target
	<< " and inflict " << this->_attack_damage << " damage" nl;
}
