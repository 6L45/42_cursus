#ifndef WEAPON_HPP
#define WEAPON_HPP

#include <iostream>
#include "Weapon.hpp"

class Weapon
{
	public :

		Weapon(std::string type = "Laser gun");
		~Weapon();
		
		std::string	getType() const;
		void 		setType(std::string);

	private :

		std::string _type;
};

#endif
