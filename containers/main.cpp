#include "vector.hpp"
#include <vector>

int	main()
{
	ft::Vector<int>			vectest;
	std::vector<int>		original;

	original.push_back(42);
	original.push_back(44);
	original.push_back(2);

	vectest.push_back(42);	
	vectest.push_back(35);
	vectest.push_back(94);
	vectest.push_back(99);

	std::vector<int>::iterator it = original.begin();
	ft::Vector<int>::iterator itest = vectest.begin();

	out itest << nl;
	out  *it << nl;

	return (0);
}
