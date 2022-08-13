# include "wrongPet.hpp"

wrongCat::wrongCat()
{
	this->type = "wrongcat";
	out "wrongCat constructor" nl;
}

wrongCat::~wrongCat()
{
	out "wrongCat destructor" nl;;
}


void	wrongCat::makeSound() const
{
	std::cout << "meeeeeeeehhh" << std::endl;
}
