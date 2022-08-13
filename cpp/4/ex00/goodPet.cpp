# include "goodPet.hpp"

/******************* CAT *******************/
Cat::Cat()
{
	this->type = "cat";
	out "Cat constructor" nl;
}

Cat::Cat(Cat const &model)
{
	this->type = model.type;
	out "cat copy constructor" nl;
}

Cat::~Cat()
{
	out "Cat destructor" nl;;
}

void	Cat::makeSound() const
{
	std::cout << "meow" << std::endl;
}

Cat	&Cat::operator=(Cat const &model)
{
	this->type = model.type;
	out "Cat equal operator overload" nl;
	return (*this);
}


/******************* DOG *******************/
Dog::Dog()
{
	this->type = "dog";
	out "dog constructor" nl;
}

Dog::Dog(Dog const &model)
{
	this->type = model.type;
	out "dog copy constructor" nl;
}

Dog::~Dog()
{
	out "dog destructor" nl;;
}

void	Dog::makeSound() const
{
	std::cout << "wouaf" << std::endl;
}

Dog	&Dog::operator=(Dog const &model)
{
	this->type = model.type;
	out "Cat equal operator overload" nl;
	return (*this);
}
