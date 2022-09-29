#include "vector.hpp"
#include <vector>
#include <iterator>

template<class T>
void	ftVCout(ft::Vector<T> &container, const char *delimiter = " ")
{
	std::copy(container.begin(), container.end(),
			std::ostream_iterator<T>(std::cout, delimiter));
}

int	main()
{
	ft::Vector<std::string>
		a = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	ft::Vector<std::string>
		b = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};

	std::copy(a.begin() + 3, a.begin() + 7, b.begin() + 6);
	ftVCout(b);

/*
	original.reserve(4);
	
	out "max : " << original.capacity() << nl;

	original.push_back(42);
	original.push_back(35);
	original.push_back(94);
	out "94 : " << &original.front() << nl;
	original.push_back(99);
	out "99 : " << &original.front() << nl;
	original.push_back(56);
	out "56 : " << &original.front() << nl;
*/

/*
	out "empty ? : " << vectest.empty() << nl;

	original.push_back(42);
	original.push_back(44);
	original.push_back(2);

	vectest.push_back(42);	
	vectest.push_back(35);
	vectest.push_back(94);
	vectest.push_back(99);

	std::vector<int>::iterator it = original.begin();
	ft::Vector<int>::iterator itest = vectest.begin();

	out vectest.at(56) << nl;
	out vectest.at(3) << nl;
	out vectest.at(-6) << nl;

	out "empty ? : " << vectest.empty() << nl;

	out "front : " <<  vectest.front() << nl;
	out vectest[2] << nl;
	out "back : " << vectest.back() << nl;

	out itest << nl;
	out  *it << nl;
*/
	return (0);
}
