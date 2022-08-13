#ifndef ZOMBIE_HPP
# define ZOMBIE_HPP

# include <iostream>
# define NL << std::endl

class Zombie
{
	public :

		Zombie(std::string);
		~Zombie(void);

		void announce() const;

	private :

		std::string _name;
};

Zombie*	newZombie(std::string name);
void	randomChump(std::string name);

#endif
