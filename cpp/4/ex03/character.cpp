#include "character.hpp"

std::string const	&Character::getName() const
{
	return (this->_name);
}

void	Character::equip(AMateria *m)
{
	;
}

void	Character::unequip(int idx)
{
	;
}

void	Character::use(int idx, ICharacter& target)
{
	_materia[idx]->use(target);
}
