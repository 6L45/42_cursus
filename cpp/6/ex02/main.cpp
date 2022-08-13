#include "classes.hpp"

int	main()
{
	srand((unsigned) time(0));

	Base	*ptr = generate();

	std::cout << "identify(Base *p) : ";
	identify(ptr);
	std::cout << "identify(Base &p) : ";
	identify(*ptr);

	delete ptr;
	return (0);
}