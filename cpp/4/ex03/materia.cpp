#include "materia.hpp"

//Destructors
Ice::~Ice()
{
	;
}

Cure::~Cure()
{
	;
}

//methods
AMateria	*Ice::clone() const
{
	return (new Ice());
}

AMateria	*Cure::clone() const
{
	return (new Cure());
}

void	Ice::use(ICharacter &target)
{
	std::cout << "* shoots an ice bolt at " << target.getName() << " *" << std::endl;
}

void	Cure::use(ICharacter &target)
{
	std::cout << "* heals " << target.getName() << "’s wounds *" << std::endl;
}
