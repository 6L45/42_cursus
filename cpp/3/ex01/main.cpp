#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int	main()
{
	ScavTrap scvtrp("Serena");

	scvtrp.attack("enemies of the nation");
	scvtrp.attack("enemies of the party");
	scvtrp.takeDamage(6);
	scvtrp.attack("anyone who doesn't accept the comrade");
	scvtrp.takeDamage(1);
	scvtrp.takeDamage(2);
	scvtrp.beRepaired(5);
	scvtrp.beRepaired(3);
	scvtrp.beRepaired(7);
	scvtrp.attack("the last opponent of the great big brother");
	scvtrp.beRepaired(9);
	scvtrp.beRepaired(5);
	scvtrp.attack("the commies");
	scvtrp.attack("the goonies");
	scvtrp.attack("the noobs");
	scvtrp.attack("Nesingwary");
	scvtrp.takeDamage(10);
	scvtrp.attack("the last stand");
	scvtrp.attack("007");
	scvtrp.guardGate();

	return (0);
}