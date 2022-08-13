#include "bureaucrat.hpp"

Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name)
{
	this->_grade = 0;
	try
	{
		if (grade > 150)
			Bureaucrat::gradeTooHightExecption();
		else if (grade < 0)
			Bureaucrat::gradeTooLowExecption();
		this->_grade = grade;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

Bureaucrat::Bureaucrat(Bureaucrat const &model) : _name(model._name)
{
	this->_grade = model._grade;
}

Bureaucrat	&Bureaucrat::operator=(Bureaucrat const &model)
{
	this->_grade = model._grade;
	return (*this);
}

Bureaucrat::~Bureaucrat() {}	

void	Bureaucrat::promotion()
{
	try
	{
		if (this->_grade - 1 == 0)
			Bureaucrat::gradeTooHightExecption();
		this->_grade--;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
}

void	Bureaucrat::retrogradation()
{
	try
	{
		if (this->_grade + 1 > 150)
			Bureaucrat::gradeTooLowExecption();
		this->_grade++;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}

void	Bureaucrat::executeForm(Form const &form) const
{
	try 
	{
		form.execute(*this);
		form.whatNeedsToBeDone();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}


void	Bureaucrat::gradeTooHightExecption()
{
	throw std::runtime_error("grade too low");
}

void	Bureaucrat::gradeTooLowExecption()
{
	throw std::runtime_error("grade too high");
}

std::string	Bureaucrat::getName() const
{
	return (this->_name);
}

int	Bureaucrat::getGrade() const
{
	return (this->_grade);
}

std::ostream	&operator<<(std::ostream &c_out, Bureaucrat &model)
{
	if (model.getGrade())
		c_out << model.getName() << ", bureaucrat grade : " << model.getGrade();
	else
		c_out << model.getName() << ", bureaucrat grade : undefined";
	return (c_out);
}
