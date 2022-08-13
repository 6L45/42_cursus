#include "intern.hpp"

Intern::Intern()
{
	this->type[0].form = "Shrubbery";
	this->type[1].form = "Robotomy";
	this->type[2].form = "Pardon";

	this->type[0].func = &Intern::Shrubber;
	this->type[1].func = &Intern::Robot;
	this->type[2].func = &Intern::PresidentialPardon;
}

Form	*Intern::Shrubber(std::string target)
{
	Form	*form = new ShrubberyCreationForm(target);
	return (form);
}

Form	*Intern::Robot(std::string target)
{
	Form	*form = new RobotomyRequestForm(target);
	return (form);
}

Form	*Intern::PresidentialPardon(std::string target)
{
	Form	*form = new PresidentialPardonForm(target);
	return (form);
}

Form	*Intern::makeForm(std::string name, std::string target)
{
	int	i = 0;

	try
	{
		while (i < 3 && this->type[i].form.compare(name))
			i++;
		if (i < 3)
			return ((this->*type[i].func)(target));
		throw std::runtime_error("invalid form name");

	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return (NULL);
}
