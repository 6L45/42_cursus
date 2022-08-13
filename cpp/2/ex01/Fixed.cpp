#include "Fixed.hpp"

//#########################################################################################
// ------------------------------------------------------------------------------CONSTRUCTS
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

Fixed::Fixed(const int int_nbr)
{
	std::cout << "Int constructor called" << std::endl;
	intToFixed(int_nbr);

}

Fixed::Fixed(const float float_nbr)
{
	std::cout << "Float constructor called" << std::endl;
	floatToFixed(float_nbr);
}


//#########################################################################################
// --------------------------------------------------------------------------PUBLIC METHODS
float	Fixed::toFloat(void) const
{
	return ((float)this->_nbr * pow(2, -(this->scale)));
}

int 	Fixed::toInt(void) const
{
	return (this->_nbr / pow(2, this->scale));
}

int	Fixed::getRawBits(void) const
{
	return (this->_nbr);
}

void	Fixed::setRawBits(int const raw)
{
	std::cout << "setRawBits member function called" << std::endl;
	this->_nbr = raw;
}

void	Fixed::intToFixed(const int int_nbr)
{
	this->_nbr = int_nbr << this->scale;
}

void	Fixed::floatToFixed(const float float_nbr)
{
	this->_nbr = roundf(float_nbr * pow(2, (this->scale)));
}

int		Fixed::getScale(void) const
{
	return (this->scale);
}

//#########################################################################################
// -----------------------------------------------------------------------OPERATOR OVERLOAD
Fixed	&Fixed::operator=(Fixed const &model)
{
	std::cout << "Assignation operator called" << std::endl;
	this->_nbr = model.getRawBits();
	return (*this);
}


std::ostream &operator<<(std::ostream &c_out, Fixed const &model)
{
	c_out << (float)(model.getRawBits()) / ((float)(1 << model.getScale()));
	return (c_out);
}

//#########################################################################################
// --------------------------------------------------------------------------------DESTRUCT
Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}