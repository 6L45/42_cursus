#include "easyfind.hpp"

int main(void)
{
	std::vector<int> vec;
	for (int i = 3; i < 11; i++)
	{
		vec.push_back(i);
	}

	std::vector<int>::iterator iter = vec.begin();
	while (iter != vec.end())
	{
		if (*iter == 4 || *iter == 8)
			std::cout << "[" << *iter <<  "] -> (" << &(*iter) << ") ";
		*iter++;
	}
	std::cout << std::endl;

	try
	{
		std::cout << "4 found! -> " << "address = " << &easyfind(vec, 4)
		<< std::endl;
		std::cout << "8 found! -> " << "address = " << &easyfind(vec, 8)
		<< std::endl;
		easyfind(vec, 12);
	}
	catch (std::exception & e)
	{
		std::cout << "Exception : " << e.what() << std::endl;
	}
	return 0;
}
