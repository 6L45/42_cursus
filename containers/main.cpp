#include "vector.hpp"
#include <vector>
#include <iterator>

template<class T>
void	ftVCout(ft::vector<T> &container, const char *delimiter = " ")
{
	std::copy(container.begin(), container.end(),
			std::ostream_iterator<T>(std::cout, delimiter));
	out nl;
}

int	main()
{
	ft::vector<std::string>
		a = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	ft::vector<std::string>
		b = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"};

	ft::vector<std::string> c(a);

	ft::vector<int> e(8);
	std::vector<int> d(8);

	out "test : " << e.size() << " " << e.capacity() << nl;
	out "orig : " << d.size() << " " << d.capacity() << nl;

	std::vector<int> w = {1, 2, 3, 4, 5, 6};
	d.assign(w.begin(), w.begin() + 3);

	out d.size() << " and " << d.capacity();
	for (std::vector<int>::iterator it = d.begin(); it != d.end(); ++it)
		out '[' << *it << "] ";
	out nl;
	ft::vector<int> z = { 1, 2, 3, 4, 5, 6};
	e.assign(z.begin(), z.begin() + 3);
	//e[3] = 5;
	ftVCout(e);

	
	std::vector<int> az ={1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> ae ={10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

	az.assign(ae.begin(), ae.begin() + 10);
	for (std::vector<int>::iterator it = az.begin(); it != az.end(); ++it)
		out '[' << *it << "] ";
	out nl;
	out az[8]<< nl;

	std::vector<int> wx(50);
	wx.assign(2, 42);
	for (std::vector<int>::iterator it = wx.begin(); it != wx.end(); ++it)
		out "-[" << *it << "]- ";
	out nl;

/*
	a.push_back("zero");
	a.push_back("one");
	a.push_back("two");
	a.push_back("three");
	a.push_back("four");
	a.push_back("five");
	a.push_back("six");
	a.push_back("seven");
	a.push_back("eight");
	a.push_back("nine");

	a.assign(5, "hehe");
	a.push_back("ten");
*/
/*	for (ft::vector<std::string>::iterator it = c.begin(); it != c.end(); it++)
		out *it << nl;

	ftVCout(c);
*/
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
	ft::vector<int>::iterator itest = vectest.begin();

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
