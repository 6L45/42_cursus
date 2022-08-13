#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>
# include <stdlib.h>
# include <ctime>

# define NL << std::endl

class Zombie
{
	public :

		Zombie(std::string name = "Unknown");
		~Zombie(void);

		void	announce() const;
		void	assign_name(std::string);

	private :

		std::string _name;
};

Zombie* zombieHorde(int N, std::string name);
Zombie* newZombie(std::string name);

#endif
