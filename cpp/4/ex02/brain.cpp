#include "brain.hpp"

Brain::Brain()
{
	;
}

Brain::Brain(Brain const &model)
{
	for (int i = 0; i < 100; i++)
		this->ideas[i] = model.ideas[i];
}

Brain	&Brain::operator=(Brain const &model)
{
	for (int i = 0; i < 100; i++)
		this->ideas[i] = model.ideas[i];
	return (*this);
}

Brain::~Brain()
{
	;
}
