#ifndef CLAP_TRAP_HPP
# define CLAP_TRAP_HPP

# include <iostream>
# define nl << std::endl
# define out std::cout <<

class ClapTrap
{
	public :
		
		ClapTrap(std::string);
		~ClapTrap();
		
		void	attack(const std::string& target);
		void	takeDamage(unsigned int amount);
		void	beRepaired(unsigned int amount);

	protected :
		std::string	_name;
		int			_hit_pts;
		int			_hit_pts_modified;
		int			_energy;
		int			_attack_damage;
		int			_alive;

		void	already_dead(void);
};

#endif
