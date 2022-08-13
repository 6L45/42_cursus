#include "goodPet.hpp"

/******************* CAT *******************/
Cat::Cat()
{
	this->type = "Cat";
	this->cerv = new Brain;
	this->cerv->ideas[0] = "pâté";
	this->cerv->ideas[1] = "sieste";
	out "cat constructor" nl;
}

Cat::Cat(Cat const &model) : Animal()
{
	this->type = "Cat";
	this->cerv = new Brain(*model.cerv);
	out "Cat copy constructor" nl;
}

Cat::~Cat()
{
	delete this->cerv;
	out "Cat destructor" nl;
}

void	Cat::makeSound() const
{
	std::cout << "meow" << std::endl;
}

void	Cat::letsSee() const
{
	out this->cerv->ideas[0] nl;
	out this->cerv->ideas[1] nl;
}

Cat	&Cat::operator=(Cat const &model)
{
	this->type = model.type;
	*this->cerv = *model.cerv;
	out "Cat equal operator overload" nl;
	return (*this);
}

/******************* DOG *******************/
Dog::Dog()
{
	this->type = "dog";
	this->cerv = new Brain;
	this->cerv->ideas[0] = "nonos";
	this->cerv->ideas[1] = "baballe";
	out "Dog constructor" nl;
}

Dog::Dog(Dog const &model) : Animal()
{
	this->type = "Dog";
	this->cerv = new Brain(*model.cerv);
	out "Dog copy constructor" nl;
}

Dog::~Dog()
{
	delete this->cerv;
	out "Dog destructor" nl;
}

void	Dog::letsSee() const
{
	out this->cerv->ideas[0] nl;
	out this->cerv->ideas[1] nl;
}

void	Dog::makeSound() const
{
	std::cout << "wouaf" << std::endl;
}

Dog	&Dog::operator=(Dog const &model)
{
	this->type = model.type;
	*this->cerv = *model.cerv;
	out "Dog equal operator overload" nl;
	return (*this);
}
