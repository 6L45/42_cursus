#ifndef CLASSES_HPP
# define CLASSES_HPP

# include <iostream>
# include <cstdlib>
# include <string>

# define out std::cout <<
# define nl << std::endl

class Base
{
	public:
		virtual ~Base() {};
	
};

class A : public Base
{
	~A() {};
};

class B : public Base
{
	~B() {};
};

class C : public Base
{
	~C() {};
};


Base	*generate(void);
void	identify(Base *p);
void	identify(Base &p);


#endif
