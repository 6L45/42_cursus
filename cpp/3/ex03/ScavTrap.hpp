#ifndef SCAV_TRAP_HPP
# define SCAV_TRAP_HPP

# include "ClapTrap.hpp"

class ScavTrap : virtual public ClapTrap
{
	public :

		ScavTrap(std::string);
		// ScavTrap();
		~ScavTrap();

		void	attack(const std::string& target);
		void	guardGate();

	private :
		std::string	_name;
};

#endif
