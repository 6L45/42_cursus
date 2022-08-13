# include "animal.hpp"

AAnimal::AAnimal()
{
	this->type = "undefined";
	out "AAnimal constructor" nl;
}
AAnimal::~AAnimal()
{
	out "AAnimal destructor" nl;
}

std::string	AAnimal::getType() const
{
	return (this->type);
}
