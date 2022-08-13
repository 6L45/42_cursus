#include "FragTrap.hpp"

FragTrap::FragTrap(std::string name): ClapTrap(name)
{
	this->_name = name;
	out "FragTrap unit on" nl;
	this->_hit_pts = 101;
	this->_hit_pts_modified = this->_hit_pts;
	this->_energy = 51;
	this->_attack_damage = 21;
}

FragTrap::~FragTrap()
{
	out "FragTrap off " nl;
}

void 	FragTrap::attack(const std::string &target)
{
	if (!this->_alive)
	{
		already_dead();
		return ;
	}
	if (!this->_energy)
	{
		out "ClapTRap : FragTrap unit " << this->_name
		<< " doesn't have any power anymore, thus, can't do now, let him rest in peace" nl;
		return ;
	}
	this->_energy--;
	out "ClapTRap FragTrap unit " << this->_name << " attack " << target
	<< " and inflict " << this->_attack_damage << " damage" nl;
}

void	FragTrap::highFivesGuys(void)
{
  out "ヘ( ^o^)ノ＼(^_^ ) high five" nl;
}
