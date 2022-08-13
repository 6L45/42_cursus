# include "animal.hpp"

Animal::Animal()
{
	this->type = "undefined";
	out "Animal constructor" nl;
}

Animal::Animal(Animal const &model)
{
	this->type = model.type;
	out "Animal copy constructor" nl;
}

Animal	&Animal::operator=(Animal const &model)
{
	this->type = model.type;
	out "Animal operator overload" nl;
	return (*this);
}


Animal::~Animal()
{
	out "Animal destructor" nl;;
}

std::string	Animal::getType() const
{
	return (this->type);
}

void	Animal::makeSound() const
{
	std::cout << "strange noise" << std::endl;
}

wrongAnimal::wrongAnimal()
{
	this->type = "undefined";
	out "Wrong animal constructor" nl;
}

wrongAnimal::~wrongAnimal()
{
	out "Wrong animal destructor" nl;;
}

std::string	wrongAnimal::getType() const
{
	return (this->type);
}

void	wrongAnimal::makeSound() const
{
	std::cout << "strange wrong noise" << std::endl;
}
