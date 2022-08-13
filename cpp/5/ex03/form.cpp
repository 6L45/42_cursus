#include "form.hpp"

/*-------------------- FORM --------------------*/

//METHODS
/****************************************************************/
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

void	Form::execute(Bureaucrat const &executor) const
{
	if (executor.getGrade() > this->_g2ex || !executor.getGrade())
		throw std::runtime_error("not qualified enough to execute this form");
	if (!this->_signed)
		throw std::runtime_error("please sign form before execution");
}

//Execptions throw
//-----------------------------------------
void	Form::gradeTooHighExecption()
{
	throw std::runtime_error("grade too high");
}

void	Form::gradeTooLowExecption()
{
	throw std::runtime_error("grade too low");
}
/****************************************************************/



//GETTER SETTER
/****************************************************************/
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
// SETTER
//--------------------------
void			Form::setSignLvl(int g2sign)
{
	this->_g2sign = g2sign;
}

void			Form::setExLvl(int g2ex)
{
	this->_g2ex = g2ex;
}

void		Form::setStatus(bool signe)
{
	this->_signed = signe;
}
/****************************************************************/



//OPERATOR OVERLOAD
/****************************************************************/
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



/*-------------------------------------- FORM+ --------------------------------------*/
          /*-------------------- ShrubberyCreationForm --------------------*/
          /*****************************************************************/

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const &model, std::string target)
: Form("Shrubbery", 145, 137)
{
	this->setStatus(model.getStatus());
	this->_target = target;
}

ShrubberyCreationForm	&ShrubberyCreationForm::operator=(ShrubberyCreationForm const &model)
{
	this->setStatus(model.getStatus());
	this->_target = model._target;
	return (*this);
}

void	ShrubberyCreationForm::whatNeedsToBeDone() const
{
	std::fstream outfile;
	outfile.open(this->_target.c_str(), std::ios::out);
	if (outfile.is_open())
	{
		outfile << "	           \\/ |    |/"			 << std::endl;
		outfile << "	    \\/ / \\||/  /_/___/_"		 << std::endl;
		outfile << "	     \\/   |/ \\/"				 << std::endl;
		outfile << "	_\\__\\_\\   |  /_____/_"		 << std::endl;
		outfile << "	       \\  | /          /"		 << std::endl;
		outfile << "	__ _-----`  |{,-----------~"	 << std::endl;
		outfile << "	        \\ }{"					 << std::endl;
		outfile << "	         }{{"					 << std::endl;
		outfile << "	         }}{"					 << std::endl;
		outfile << "	         {{}"					 << std::endl;
		outfile << "       , -=-~{ .-^- _"				 << std::endl;
		outfile.close();
	}
	else
		std::cout << "fail to open file : " << this->_target << std::endl;
}

           /*--------------------- RobotomyRequestForm ---------------------*/
           /*****************************************************************/

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &model, std::string target)
: Form("Robotomy", 72, 45)
{
	this->setStatus(model.getStatus());
	this->_target = target;
}

RobotomyRequestForm	&RobotomyRequestForm::operator=(RobotomyRequestForm const &model)
{
	this->setStatus(model.getStatus());
	this->_target = model._target;
	return (*this);
}

void	RobotomyRequestForm::whatNeedsToBeDone() const
{
	std::cout << "BBBzZZzzzZZZZ VshHHHhhhhIiiiiiI pzZZzt Bzz ting ting tac PAF booUUUUM..." << std::endl;
	if (rand() % 2)
		std::cout << this->_target << ": has been robotized with succes" << std::endl;
	else
		std::cout << this->_target << ": robotization failed, may he rest in peace" << std::endl;
}

           /*-------------------- PresidentialPardonForm --------------------*/
           /*****************************************************************/

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &model, std::string target)
: Form("Pardon", 25, 5)
{
	this->setStatus(model.getStatus());
	this->_target = target;
}

PresidentialPardonForm	&PresidentialPardonForm::operator=(PresidentialPardonForm const &model)
{
	this->setStatus(model.getStatus());
	this->_target = model._target;
	return (*this);
}

void	PresidentialPardonForm::whatNeedsToBeDone() const
{
	std::cout << this->_target << ": has been forgiven" << std::endl;
}
