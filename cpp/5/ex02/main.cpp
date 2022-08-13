#include "bureaucrat.hpp"
#include "form.hpp"

void	canon_tester(Bureaucrat &officer1, Bureaucrat &officer2)
{
	Bureaucrat test(officer1);
	Bureaucrat test2("Joey", 42);
	test2 = officer2;

	std::cout << "Bureaucrat" << std::endl;
	std::cout << test << std::endl;
	std::cout << test2 << std::endl;
	std::cout << std::endl;
}
void	canon_tester(ShrubberyCreationForm &form1, ShrubberyCreationForm &form2)
{
	ShrubberyCreationForm frm1(form1);
	ShrubberyCreationForm frm2("zoo");

	frm2 = form2;

	std::cout << "ShrubberyCreationForm" << std::endl;
	std::cout << frm1 << std::endl << std::endl;
	std::cout << frm2 << std::endl << std::endl;
	std::cout << std::endl;
}
void	canon_tester(RobotomyRequestForm &form1, RobotomyRequestForm &form2)
{
	RobotomyRequestForm frm1(form1);
	RobotomyRequestForm frm2("Chuck");

	frm2 = form2;

	std::cout << "RobotomyRequestForm" << std::endl;
	std::cout << frm1 << std::endl << std::endl;
	std::cout << frm2 << std::endl << std::endl;
	std::cout << std::endl;
}
void	canon_tester(PresidentialPardonForm &form1, PresidentialPardonForm &form2)
{
	PresidentialPardonForm frm1(form1);
	PresidentialPardonForm frm2("Nourice");

	frm2 = form2;

	std::cout << "PresidentialPardonForm" << std::endl;
	std::cout << frm1 << std::endl << std::endl;
	std::cout << frm2 << std::endl << std::endl;
	std::cout << std::endl;
}


int	main()
{
	Bureaucrat	officer1("Bob", 150);
	Bureaucrat	officer2("Roger", 156);
	Bureaucrat	officer3("Maurice", -2);
	Bureaucrat	officer4("Joe", 1);

	std::cout << std::endl;

	ShrubberyCreationForm form1("jardin");
	ShrubberyCreationForm form2("parc");
	RobotomyRequestForm form3("Karl");
	RobotomyRequestForm form4("chuck");
	PresidentialPardonForm form5("Jodie");
	PresidentialPardonForm form6("Moore");

	canon_tester(officer1, officer2);
	canon_tester(form1, form2);
	canon_tester(form3, form4);
	canon_tester(form5, form6);

	officer1.executeForm(form2);
	officer4.executeForm(form2);
	form2.beSigned(officer4);
	officer4.executeForm(form2);

	std::cout << std::endl;

	officer1.executeForm(form3);
	officer4.executeForm(form3);
	form3.beSigned(officer4);
	officer4.executeForm(form3);

	std::cout << std::endl;

	officer1.executeForm(form5);
	officer4.executeForm(form5);
	form5.beSigned(officer4);
	officer4.executeForm(form5);

	return (0);
}