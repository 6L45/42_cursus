#include "zombie.hpp"

Zombie* newZombie(std::string name)
{
	Zombie *ghoul;

	ghoul = new Zombie(name);
	return (ghoul);
}

int	main(int argc, char **argv)
{
	if (argc < 3)
		return (0);

	int	N;
	Zombie	*horde;

	if (!(N = atoi(argv[1])))
		return (0);
	horde = zombieHorde(atoi(argv[1]), argv[2]);
	for (int i = 0; i < N; i++)
		horde[i].announce();
	delete [] horde;
	return (0);
}
