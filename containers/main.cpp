#include "vector.hpp"
#include <vector>
#include <iterator>

template<class T>
void	ftVCout(std::vector<T> &container, const char *delimiter = " ")
{
	std::copy(container.begin(), container.end(),
			std::ostream_iterator<T>(std::cout, delimiter));
	out nl;
}

int	main()
{
	/*
	{
		ft::vector<int>	a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
		ft::vector<int> b(126);
		ft::vector<int> c;

		a.insert(a.begin() + 4, 5, -1);
	}
*/	{

	//	SI Vector vide = segfault    vide ==> non initialisé ou cleared
	//	SI pos out of rande error = free(): invalid pointer Abandon (core dumped)

	//	DONC doit y'avoir données dans le vector ET la position doit être comprise dans size()


		std::vector<int>	a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
		std::vector<int> b(126);
		std::vector<int> c(5);

		out a.capacity() << nl;

//		a.clear();

		out a.capacity() << nl;
		out a.size() << nl;

		a.insert(a.begin() + 4, 5, -1);
		b.insert(b.begin() + 10, 5, 42);
		c.insert(c.begin() + 6, 5, 44);

		out a.capacity() << nl;

		ftVCout(a);
		out nl << nl;
		ftVCout(b);
		out nl << nl;
		ftVCout(c);
	}
/*

	std::vector<int> a;
	std::vector<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	std::copy(b.begin(), b.end(), a.begin());
*/
/*
	{
		ft::vector<int> e1;
		ft::vector<int> e2;
		ft::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		ft::vector<int> ab = {1, 2, 3, 4, 4, 6, 7, 8, 9};
		ft::vector<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
		ft::vector<int> c = a;

		out "FT VECTOR ------ " << nl;

		if (e1 <= e2)
			out "e1 <= e2" << nl;
		if (e2 <= e1)
			out "e2 <= e1" << nl;
		if (a <= e1)
			out "a <= e1" << nl;
		if (e1 <= a)
			out "e1 <= a" << nl;
		if (a <= b)
			out  "a <= b" << nl;
		if (b <= a)
			out "b <= a" << nl;
		if (a <= ab)
			out "a <= ab" << nl;
		if (ab <= a)
			out "ab <= a" << nl;
		if (a <= c)
			out "a <= c" << nl;
		if (c <= a)
			out "c <= a" << nl;
	}	

	{
		std::vector<int> e1;
		std::vector<int> e2;
		std::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		std::vector<int> ab = {1, 2, 3, 4, 4, 6, 7, 8, 9};
		std::vector<int> b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
		std::vector<int> c = a;

		out "STD VECTOR ------ " << nl;

		if (e1 <= e2)
			out "e1 <= e2" << nl;
		if (e2 <= e1)
			out "e2 <= e1" << nl;
		if (a <= e1)
			out "a <= e1" << nl;
		if (e1 <= a)
			out "e1 <= a" << nl;
		if (a <= b)
			out  "a <= b" << nl;
		if (b <= a)
			out "b <= a" << nl;
		if (a <= ab)
			out "a <= ab" << nl;
		if (ab <= a)
			out "ab <= a" << nl;
		if (a <= c)
			out "a <= c" << nl;
		if (c <= a)
			out "c <= a" << nl;
	}
*/	/*
	{
		ft::vector<int> vct(5);
		ft::vector<int>::iterator it = vct.begin(), ite = vct.end();

		std::cout << "len: " << (ite - it) << std::endl;
		for (; it != ite; ++it)
			*it = (ite - it);

		it = vct.begin();

		ft::vector<int> vct_range(it, --(--ite));
		for (int i = 0; it != ite; ++it)
			*it = ++i * 5;

		it = vct.begin();
		
		ft::vector<int> vct_copy(vct);
		for (int i = 0; it != ite; ++it)
			*it = ++i * 7;
		
		out "vcp_copy size : " << vct_copy.size() << " vct_copy capacity : " << vct_copy.capacity() << nl; 
		out "vcp_range size : " << vct_range.size() << " vct_range capacity : " << vct_range.capacity() << nl;
		vct_copy.push_back(42);
		out "vcp_copy size : " << vct_copy.size() << " vct_copy capacity : " << vct_copy.capacity() << nl; 
		out "vcp_range size : " << vct_range.size() << " vct_range capacity : " << vct_range.capacity() << nl;
		vct_copy.push_back(21);
		out "vcp_copy size : " << vct_copy.size() << " vct_copy capacity : " << vct_copy.capacity() << nl; 
		out "vcp_range size : " << vct_range.size() << " vct_range capacity : " << vct_range.capacity() << nl;

		std::cout << "\t-- PART ONE --" << std::endl;

		vct = vct_copy;
		vct_copy = vct_range;
		vct_range.clear();
	}
	{
		std::vector<int> vct(5);
		std::vector<int>::iterator it = vct.begin(), ite = vct.end();

		std::cout << "len: " << (ite - it) << std::endl;
		for (; it != ite; ++it)
			*it = (ite - it);

		it = vct.begin();
		
		std::vector<int> vct_range(it, --(--ite));
		for (int i = 0; it != ite; ++it)
			*it = ++i * 5;

		it = vct.begin();

		std::vector<int> vct_copy(vct);
		for (int i = 0; it != ite; ++it)
			*it = ++i * 7;
		
		out "vcp_copy size : " << vct_copy.size() << " vct_copy capacity : " << vct_copy.capacity() << nl; 
		out "vcp_range size : " << vct_range.size() << " vct_range capacity : " << vct_range.capacity() << nl;
		vct_copy.push_back(42);
		out "vcp_copy size : " << vct_copy.size() << " vct_copy capacity : " << vct_copy.capacity() << nl; 
		out "vcp_range size : " << vct_range.size() << " vct_range capacity : " << vct_range.capacity() << nl;
		vct_copy.push_back(21);
		out "vcp_copy size : " << vct_copy.size() << " vct_copy capacity : " << vct_copy.capacity() << nl; 
		out "vcp_range size : " << vct_range.size() << " vct_range capacity : " << vct_range.capacity() << nl;

		std::cout << "\t-- PART ONE --" << std::endl;

		vct = vct_copy;
		vct_copy = vct_range;
		vct_range.clear();
	}

	std::cout << "\t-- PART TWO --" << std::endl;
*/
	/*
	ft::vector<int> vct(5);
	ft::vector<int>::iterator it = vct.begin(), ite = vct.end();

	std::cout << "len: " << (ite - it) << std::endl;
//	for (; it != ite; ++it)
		*it = (ite - it); */
	/*
	ft::vector<int> a;
	std::vector<int> b;

	out b[0] << nl;
*/
/*
	a.assign(3, 42);

	out a[2] << nl;

	a.assign(b.begin(), b.begin() + 5);
	out a.capacity() << " " << a.size() << nl;


	//a.assign(3, 42);

*/

/*
	ft::vector<int> a = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	ft::vector<int> b;

	b.push_back(0);
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);
	b.push_back(4);
	b.push_back(5);
	b.push_back(6);
	b.push_back(8);
	b.push_back(9);

	ft::vector<int> c(30);

	std::copy(a.begin(), a.end(), c.begin());

	ft::vector<int>::iterator	test = b.end();
	const ft::vector<int>::iterator	test2 = b.end();
	ft::vector<int>::iterator	test3 = b.begin();
	
	if (test <= test2)	
		out "la" << nl;

	ft::random_access_iterator<int>::difference_type	haha = test3 < test2;
	out haha << nl;

	ft::vector<int>::iterator hehe = a.begin() + haha;
	out *hehe << nl;


	out "---------------------------------------------" << nl;

	for (ft::vector<int>::iterator it = c.begin(); it != c.end(); ++it)
	{
		out  *it << nl;
		out it << nl;
	}
*/
/*
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
*/
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
