#include "zombie.hpp"

int	main(void)
{
	Zombie bob("Bob");
	Zombie charlie("Charlie");
	Zombie *hector;

	bob.announce();
	hector = newZombie("Hector");
	charlie.announce();
	hector->announce();
	randomChump("Joe");
	delete hector;

	return (0);
}
