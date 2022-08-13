#include <iostream>

#define NL << std::endl

int	main()
{
	std::string hello_brain = "HI THIS IS BRAIN";
	std::string *stringPTR = &hello_brain;
	std::string &stringREF = hello_brain;

	std::cout << "address str    : " << &hello_brain NL;
	std::cout << "address strPTR : " << stringPTR NL;
	std::cout << "address strREF : " <<  &stringREF NL;

	std::cout NL;

	std::cout << "value str      : " << hello_brain NL;
	std::cout << "value strPTR   : " << *stringPTR NL;
	std::cout << "value strREF   : " << stringREF NL;
	return (0);
}