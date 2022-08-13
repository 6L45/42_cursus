#include "ClapTrap.hpp"
#include "FragTrap.hpp"

int	main()
{
	FragTrap frptrp("Serena");

	frptrp.attack("enemies of the nation");
	frptrp.attack("enemies of the party");
	frptrp.takeDamage(6);
	frptrp.attack("anyone who doesn't accept the comrade");
	frptrp.takeDamage(1);
	frptrp.takeDamage(2);
	frptrp.beRepaired(5);
	frptrp.beRepaired(3);
	frptrp.beRepaired(7);
	frptrp.attack("the last opponent of the great big brother");
	frptrp.beRepaired(9);
	frptrp.beRepaired(5);
	frptrp.attack("the commies");
	frptrp.attack("the goonies");
	frptrp.attack("the noobs");
	frptrp.attack("Nesingwary");
	frptrp.takeDamage(10);
	frptrp.attack("the last stand");
	frptrp.attack("007");
	frptrp.highFivesGuys();

	return (0);
}