#include "Fixed.hpp"

const int scale = 8;

Fixed::Fixed()
{
	std::cout << "Default constructor called" << std::endl;
	this->_nbr = 0;
}

Fixed::Fixed(Fixed const &model)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = model;
}

Fixed	&Fixed::operator=(Fixed const &model)
{
	std::cout << "Assignation operator called" << std::endl;
	this->_nbr = model.getRawBits();
	return (*this);
}

Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

int	Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return (this->_nbr);
}

void	Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;
}
