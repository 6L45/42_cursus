#include "ClapTrap.hpp"

int	main()
{
	ClapTrap clptrp("SadTrap");

	clptrp.attack("enemies of the nation");
	clptrp.attack("enemies of the party");
	clptrp.takeDamage(6);
	clptrp.attack("anyone who doesn't accept the comrade way of life");
	clptrp.takeDamage(1);
	clptrp.takeDamage(2);
	clptrp.beRepaired(5);
	clptrp.beRepaired(3);
	clptrp.beRepaired(7);
	clptrp.attack("the last opponent of the great big brother");
	clptrp.beRepaired(9);
	clptrp.beRepaired(5);
	clptrp.attack("the commies");
	clptrp.attack("the goonies");
	clptrp.attack("the noobs");
	clptrp.attack("Nesingwary");
	clptrp.takeDamage(10);
	clptrp.attack("the last stand");
	clptrp.attack("007");

	return (0);
}