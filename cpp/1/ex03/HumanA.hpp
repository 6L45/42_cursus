#ifndef HUMANA_HPP
#define HUMANA_HPP

#include <iostream>
#include "Weapon.hpp"


class c
{
public:
  c(int & a) : i(a) { }
  int & i;
};

class HumanA
{
	public :

		HumanA(std::string name, Weapon &weapon) : _name(name), _weapon(weapon){};
		~HumanA();
		void	attack(void);

	private :

		std::string 	_name;
		Weapon			&_weapon;
};

#endif
