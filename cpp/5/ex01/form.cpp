#include "form.hpp"

Form::Form(std::string name, int g2sign, int g2ex) : _name(name)
{
	this->_g2sign = 0;
	this->_g2ex = 0;
	this->_signed = false;
	try
	{
		if (g2sign < 0 || g2ex < 0)
			Form::gradeTooHighExecption();
		else if (g2sign > 150 || g2ex > 150)
			Form::gradeTooLowExecption();
		this->_g2sign = g2sign;
		this->_g2ex = g2ex;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

Form::Form(Form const &model)
{
	this->_name = model._name;
	this->_signed = model._signed;
	this->_g2ex = model._g2ex;
	this->_g2sign = model._g2sign;
}

Form	&Form::operator=(Form const &model)
{
	this->_name = model.getName();
	this->_signed = model.getStatus();
	this->_g2ex = model.getExLvl();
	this->_g2sign = model.getSignLvl();
	return (*this);
}

void	Form::beSigned(const Bureaucrat &officer)
{
	try
	{
		if (officer.getGrade() && this->_g2sign && officer.getGrade() > this->_g2sign)
			throw std::runtime_error("he's not high enough in the hierarchy to sign that paper");
		else if (!this->_g2sign)
			throw std::runtime_error("Invalid document. Please refer issue to the hierarchy");
		else if (!officer.getGrade())
			throw std::runtime_error("unquilified grade can't sign documents. Please addrese your situation to the hierarchy");	
		std::cout << officer.getName() << " signed " << this->_name << std::endl;
		this->_signed = true;
	}
	catch(const std::exception& e)
	{
		std::cerr << officer.getName() <<  " couldn't sign "
					<< this->_name << " because "  << e.what() << std::endl;
	}
	
}

void	Form::gradeTooHighExecption()
{
	throw std::runtime_error("grade too high");
}

void	Form::gradeTooLowExecption()
{
	throw std::runtime_error("grade too low");
}

std::string	Form::getName() const
{
	return (this->_name);
}

int			Form::getSignLvl() const
{
	return (this->_g2sign);
}

int			Form::getExLvl() const
{
	return (this->_g2ex);
}

bool		Form::getStatus() const
{
	return (this->_signed);
}

std::ostream	&operator<<(std::ostream &c_out, Form &model)
{
	c_out << "Form " << model.getName() << std::endl
	<< "approbation level : ";
	if (model.getSignLvl())
		c_out << model.getSignLvl();
	else
		c_out << "undefined";
	c_out << std::endl << "execution level : ";
	if (model.getExLvl())
		c_out << model.getExLvl() << std::endl;
	else
		c_out << "undefined" << std::endl;
	if (model.getStatus())
		c_out << "SIGNED";
	else
		c_out << "UNSIGNED";
	return (c_out);
}
