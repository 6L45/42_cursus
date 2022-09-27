#include "vector.hpp"
#include <vector>

int	main()
{
	ft::Vector<int>			vectest;
	ft::Vector<int>		original;


	vectest.push_back(42);	
	vectest.push_back(35);
	vectest.push_back(94);
	vectest.push_back(99);
	vectest.push_back(56);

	original.push_back(0);
	original.push_back(1);
	original.push_back(2);
	original.push_back(3);
	original.push_back(4);


	out vectest.at(2) << nl;
	vectest.swap(original);
	out vectest.at(2) << nl ;
	out vectest.back() << nl;

	vectest.clear();
	out vectest.size() << nl;
	vectest.push_back(42);
	out vectest.size() << nl;
	out vectest.back() << nl;

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
