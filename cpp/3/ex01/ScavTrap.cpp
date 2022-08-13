#include "ScavTrap.hpp"

ScavTrap::ScavTrap(std::string name): ClapTrap(name)
{
	this->_name = name;
	out "ScavTrap unit on" nl;
	this->_hit_pts = 100;
	this->_hit_pts_modified = this->_hit_pts;
	this->_energy = 50;
	this->_attack_damage = 20;
}

ScavTrap::~ScavTrap()
{
	out "ScavTrap off " nl;
}

void 	ScavTrap::attack(const std::string &target)
{
	if (!this->_alive)
	{
		already_dead();
		return ;
	}
	if (!this->_energy)
	{
		out "ClapTRap : ScavTrap unit " << this->_name
		<< " doesn't have any power anymore, thus, can't do now, let him rest in peace" nl;
		return ;
	}
	this->_energy--;
	out "ClapTRap ScavTrap unit " << this->_name << " attack " << target
	<< " and inflict " << this->_attack_damage << " damage" nl;
}

void	ScavTrap::guardGate(void)
{
	out "Guardian at the gate. \"¡No pasarán!\"" nl;
}
