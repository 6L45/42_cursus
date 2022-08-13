#include "zombie.hpp"

Zombie* newZombie(std::string name)
{
	Zombie *ghoul;

	ghoul = new Zombie(name);
	return (ghoul);
}
