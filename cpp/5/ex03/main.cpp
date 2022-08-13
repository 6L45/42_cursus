#include "bureaucrat.hpp"
#include "form.hpp"
#include "intern.hpp"

int	main()
{
	Bureaucrat	officer1("Bob", 150);
	Bureaucrat	officer4("Joe", 1);

	Intern	someRandomIntern;
	Form	*form1;
	Form	*form2;
	Form	*form3;
	// Form	*form4;

	form1 = someRandomIntern.makeForm("Shrubbery", "jardin");
	form2 = someRandomIntern.makeForm("Robotomy", "parc");
	form3 = someRandomIntern.makeForm("Pardon", "Karl");
	// form4 = someRandomIntern.makeForm("random", "Karl");
	// if (!form4)
	// {
	// 	delete form1;
	// 	delete form2;
	// 	delete form3;
	// 	return (0);
	// }

	officer1.executeForm(*form1);
	officer4.executeForm(*form1);
	form1->beSigned(officer4);
	officer4.executeForm(*form1);
	

	std::cout << std::endl;

	officer1.executeForm(*form2);
	officer4.executeForm(*form2);
	form2->beSigned(officer4);
	officer4.executeForm(*form2);
	

	std::cout << std::endl;

	officer1.executeForm(*form3);
	officer4.executeForm(*form3);
	form3->beSigned(officer4);
	officer4.executeForm(*form3);

	delete form1;
	delete form2;
	delete form3;
	// delete form4;

	return (0);
}