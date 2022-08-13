#include "ClapTrap.hpp"

ClapTrap::ClapTrap(std::string name)
{
	this->_name = name;
	out "ClapTRap " << this->_name << " is in da place !" nl;
	this->_hit_pts = 10;
	this->_energy = 10;
	this->_attack_damage = 0;
	this->_alive = 1;
}

ClapTrap::~ClapTrap()
{
	out "ClapTRap " << this->_name
	<< " is dead, but do not despair. It's gone for a better world" 
	<< " it's now isekaied, merely the cycle of life... Hakuna matata !!!" nl;
}

void	ClapTrap::already_dead()
{
	out "RIP " << "ClapTRap " << this->_name << " May it be never forgotten" nl;
}

void 	ClapTrap::attack(const std::string& target)
{
	if (!this->_alive)
	{
		already_dead();
		return ;
	}
	if (!this->_energy)
	{
		out "ClapTRap " << this->_name
		<< " doesn't have any power anymore, thus, can't do anything anymore now, let it rest in peace" nl;
		return ;
	}
	this->_energy--;
	out "ClapTRap " << this->_name << " attack " << target
	<< " and inflict " << this->_attack_damage << " damage" nl;
}

void 	ClapTrap::takeDamage(unsigned int amount)
{
	if (!this->_alive)
	{
		already_dead();
		return ;
	}
	out "ClapTRap " << this->_name
	<< " receive " << amount << " of damage" nl;
	this->_hit_pts -= amount;
	if (this->_hit_pts <= 0)
		this->_alive = 0;
}

void 	ClapTrap::beRepaired(unsigned int amount)
{
	if (!this->_alive)
	{
		already_dead();
		return ;
	}
	if (!this->_energy)
	{
		out "ClapTRap " << this->_name << " doesn't have any power anymore, thus, can't do anything anymore" nl;
		return ;
	}
	if (this->_hit_pts == 10)
	{
		out "ClapTRap " << this->_name << " already full life nothing's done" nl;
		return ;
	}
	this->_energy--;
	if (this->_hit_pts + amount > 10)
		amount = 10 - this->_hit_pts;
	out "ClapTRap " << this->_name << " proceed to repair itself and gain " << amount << " health back" nl;
	this->_hit_pts += amount;
}