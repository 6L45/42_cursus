#include "bureaucrat.hpp"

void	canon_tester(Bureaucrat &officer1, Bureaucrat &officer2)
{
	Bureaucrat test(officer1);
	Bureaucrat test2("unknown", 42);
	test2 = officer2;

	std::cout << test.getGrade() << std::endl;
	std::cout << test2.getGrade() << std::endl;
}

int	main()
{
	Bureaucrat	officer1("Bob", 150);
	Bureaucrat	officer2("Roger", 156);
	Bureaucrat	officer3("Maurice", -2);
	Bureaucrat	officer4("Joe", 1);

	canon_tester(officer1, officer2);

	std::cout << officer1.getGrade() << std::endl;
	std::cout << officer2.getGrade() << std::endl;
	std::cout << officer3.getGrade() << std::endl;
	std::cout << officer4.getGrade() << std::endl;

	officer4.promotion();
	officer1.retrogradation();

	std::cout << officer1.getGrade() << std::endl;
	std::cout << officer4.getGrade() << std::endl;

	officer4.retrogradation();
	officer1.promotion();

	std::cout << officer1 << std::endl;
	std::cout << officer2 << std::endl;
	std::cout << officer3 << std::endl;
	std::cout << officer4 << std::endl;
	
	return (0);
}