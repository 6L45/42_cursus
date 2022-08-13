#include "zombie.hpp"

void randomChump(std::string name)
{
	Zombie *joe;

	joe = new Zombie(name);
	joe->announce();
	delete joe;
}
