#include "bureaucrat.hpp"
#include "form.hpp"

void	canon_tester(Bureaucrat &officer1, Bureaucrat &officer2, Form &form1, Form &form2)
{
	Bureaucrat test(officer1);
	Bureaucrat test2("unknown", 42);
	test2 = officer2;

	Form ftst1(form1);
	Form ftst2("95D", 1, 1);
	ftst2 = form2;

	std::cout << test.getGrade() << std::endl;
	std::cout << test2.getGrade() << std::endl;

	std::cout << ftst1 << std::endl << std::endl; 
	std::cout << ftst2 << std::endl << std::endl; 
}

int	main()
{
	Bureaucrat	officer1("Bob", 150);
	Bureaucrat	officer2("Roger", 156);
	Bureaucrat	officer3("Maurice", -2);
	Bureaucrat	officer4("Joe", 1);

	std::cout << std::endl;

	Form		form1("28B", 42, 21);
	Form		form2("29B", 152, 21);
	Form		form3("01C", 42, 153);	
	Form		form4("02C", -1, 21);
	Form		form5("03C", 42, -21);
	Form		form6("04C", -42, -21);
	Form		form7("05C", 152, 171);
	Form		form8("06C", -152, 171);


	canon_tester(officer1, officer2, form1, form2);

	std::cout << std::endl;

	std::cout << officer1.getGrade() << std::endl;
	std::cout << officer2.getGrade() << std::endl;
	std::cout << officer3.getGrade() << std::endl;
	std::cout << officer4.getGrade() << std::endl;

	officer4.promotion();
	officer1.retrogradation();

	std::cout << std::endl;

	std::cout << officer1.getGrade() << std::endl;
	std::cout << officer4.getGrade() << std::endl;

	std::cout << std::endl;

	officer4.retrogradation();
	officer1.promotion();

	std::cout << officer1 << std::endl;
	std::cout << officer2 << std::endl;
	std::cout << officer3 << std::endl;
	std::cout << officer4 << std::endl << std::endl;

	std::cout << form1 << std::endl << std::endl; 
	std::cout << form2 << std::endl << std::endl; 
	std::cout << form3 << std::endl << std::endl; 
	std::cout << form4 << std::endl << std::endl; 
	std::cout << form5 << std::endl << std::endl; 
	std::cout << form6 << std::endl << std::endl; 
	std::cout << form7 << std::endl << std::endl; 
	std::cout << form8 << std::endl << std::endl; 


	form1.beSigned(officer2);
	form2.beSigned(officer3);
	form3.beSigned(officer1);
	form4.beSigned(officer1);
	form5.beSigned(officer1);
	form6.beSigned(officer1);
	form7.beSigned(officer1);
	form8.beSigned(officer1);

	std::cout << std::endl;

	std::cout << form1 << std::endl << std::endl; 
	std::cout << form2 << std::endl << std::endl; 
	std::cout << form3 << std::endl << std::endl; 
	std::cout << form4 << std::endl << std::endl; 
	std::cout << form5 << std::endl << std::endl; 
	std::cout << form6 << std::endl << std::endl; 
	std::cout << form7 << std::endl << std::endl; 
	std::cout << form8 << std::endl << std::endl;

	std::cout << std::endl;

	form1.beSigned(officer4);
	form2.beSigned(officer4);
	form3.beSigned(officer4);
	form4.beSigned(officer4);
	form5.beSigned(officer4);
	form6.beSigned(officer4);
	form7.beSigned(officer4);
	form8.beSigned(officer4);

	std::cout << std::endl;

	std::cout << form1 << std::endl << std::endl; 
	std::cout << form2 << std::endl << std::endl; 
	std::cout << form3 << std::endl << std::endl; 
	std::cout << form4 << std::endl << std::endl; 
	std::cout << form5 << std::endl << std::endl; 
	std::cout << form6 << std::endl << std::endl; 
	std::cout << form7 << std::endl << std::endl; 
	std::cout << form8 << std::endl << std::endl;

	return (0);
}