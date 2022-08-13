#include <iostream>
#include "convert.hpp"

#define out std::cout <<
#define nl << std::endl

int main(int argc, char **argv)
{
	std::string arg;

	if (argc < 2)
		return (0);
	
	arg = argv[1];
	Convert cast(arg);
	
	cast.print();
	return (0);
}