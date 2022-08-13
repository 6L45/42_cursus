#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"

void	main_humanA(void)
{
	Weapon club = Weapon("crude spiked club");
	HumanA bob("Bob", club);
	bob.attack();
	club.setType("some other type of club");
	bob.attack();
}

void	main_humanB(void)
{
	Weapon club = Weapon("crude spiked club");
	HumanB jim("Jim");
	jim.setWeapon(club);
	jim.attack();
	club.setType("some other type of club");
	jim.attack();
}

int	main()
{
	main_humanA();
	std::cout << std::endl;
	main_humanB();
	return (0);
}
