# include "ClapTrap.hpp"
# include "FragTrap.hpp"
# include "ScavTrap.hpp"
# include "DiamondTrap.hpp"

void	claptrapClassMain()
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
}

void	scavtrapClassMain()
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
}

void	fragtrapClassMain()
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
}

void	diamondtrapClassMain()
{
	DiamondTrap dimdtrp("Jewel");

	dimdtrp.attack("enemies of the nation");
	dimdtrp.attack("enemies of the party");
	dimdtrp.takeDamage(6);
	dimdtrp.attack("anyone who doesn't accept the comrade");
	dimdtrp.takeDamage(1);
	dimdtrp.takeDamage(2);
	dimdtrp.beRepaired(5);
	dimdtrp.beRepaired(3);
	dimdtrp.beRepaired(7);
	dimdtrp.attack("the last opponent of the great big brother");
	dimdtrp.beRepaired(9);
	dimdtrp.beRepaired(5);
	dimdtrp.attack("the commies");
	dimdtrp.attack("the goonies");
	dimdtrp.attack("the noobs");
	dimdtrp.attack("Nesingwary");
	dimdtrp.takeDamage(10);
	dimdtrp.attack("the last stand");
	dimdtrp.attack("007");
	dimdtrp.highFivesGuys();
	dimdtrp.whoAmI();
	dimdtrp.guardGate();
}

int	main()
{
	claptrapClassMain();
	out std::endl;
	out std::endl;
	fragtrapClassMain();
	out std::endl;
	out std::endl;
	scavtrapClassMain();
	out std::endl;
	out std::endl;
	diamondtrapClassMain();
	
	return (0);
}