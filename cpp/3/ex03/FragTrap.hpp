#ifndef FRAG_TRAP_HPP
# define FRAG_TRAP_HPP

# include "ClapTrap.hpp"

class FragTrap : virtual public ClapTrap
{
	public :

		FragTrap(std::string);
		// FragTrap();
		~FragTrap();

		void	attack(const std::string& target);
		void	highFivesGuys(void);

	private :
		std::string	_name;
};

#endif
