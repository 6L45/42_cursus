#include "classes.hpp"

Base	*generate(void)
{
	int randomNumber = rand();
	
	if (randomNumber % 3 == 0)
		return (new A);
	else if (randomNumber % 3 == 1)
		return (new B);
	else if (randomNumber % 3 == 2)
		return (new C);
	return (NULL);
}

void identify(Base *p)
{
	if (dynamic_cast<A*>(p) != NULL)
		out "A" nl;
	else if (dynamic_cast<B*>(p) != NULL)
		out "B" nl;
	else if (dynamic_cast<C*>(p) != NULL)
		out "C" nl;
}

void identify(Base &p)
{
	identify(&p);
}

