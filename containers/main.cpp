#include "vector.hpp"
#include "stack.hpp"
#include <vector>
#include <iterator>
#include <stack>

template <typename Ite_1, typename Ite_2>
void ft_eq_ope(const Ite_1 &first, const Ite_2 &second, const bool redo = 1)
{
	std::cout << (first < second) << std::endl;
	std::cout << (first <= second) << std::endl;
	std::cout << (first > second) << std::endl;
	std::cout << (first >= second) << std::endl;
	if (redo)
		ft_eq_ope(second, first, 0);
}

template <typename T>
void	printSize(std::vector<T> const &vct, bool print_content = true)
{
	const size_t size = vct.size();
	const size_t capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename std::vector<T>::const_iterator it = vct.begin();
		typename std::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}


template <typename T>
void	printSize(ft::vector<T> const &vct, bool print_content = true)
{
	const size_t size = vct.size();
	const size_t capacity = vct.capacity();
	const std::string isCapacityOk = (capacity >= size) ? "OK" : "KO";
	// Cannot limit capacity's max value because it's implementation dependent

	std::cout << "size: " << size << std::endl;
	std::cout << "capacity: " << isCapacityOk << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename ft::vector<T>::const_iterator it = vct.begin();
		typename ft::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
			std::cout << "- " << *it << std::endl;
	}
	std::cout << "###############################################" << std::endl;
}

template<class T>
void	ftVCout(std::vector<T> &container, const char *delimiter = " ")
{
	std::copy(container.begin(), container.end(),
			std::ostream_iterator<T>(std::cout, delimiter));
	out nl;
}

template<class T>
void	ftVCout(ft::vector<T> &container, const char *delimiter = " ")
{
	std::copy(container.begin(), container.end(),
			std::ostream_iterator<T>(std::cout, delimiter));
	out nl;
}

template <class T, class Alloc>
void	cmp(const ft::vector<T, Alloc> &lhs, const ft::vector<T, Alloc> &rhs)
{
	static int i = 0;

	if (i == 4)
	{
		printSize(lhs);
		printSize(rhs);
		out nl << nl;
	}

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

template <class T, class Alloc>
void	cmp(const std::vector<T, Alloc> &lhs, const std::vector<T, Alloc> &rhs)
{
	static int i = 0;

	std::cout << "############### [" << i++ << "] ###############"  << std::endl;
	std::cout << "eq: " << (lhs == rhs) << " | ne: " << (lhs != rhs) << std::endl;
	std::cout << "lt: " << (lhs <  rhs) << " | le: " << (lhs <= rhs) << std::endl;
	std::cout << "gt: " << (lhs >  rhs) << " | ge: " << (lhs >= rhs) << std::endl;
}

void	is_empty(ft::vector<int> const &vct)
{
	out "------------------------------> " << vct.size() << "<------------------------------------";
	std::cout << "is_empty: " << vct.empty() << std::endl;
}

void	is_empty(std::vector<int> const &vct)
{
	out "------------------------------> ";
	std::cout << "is_empty: " << vct.empty() << std::endl;
}

template <typename T>
class foo {
	public:
		typedef T	value_type;

		foo(void) : value(), _verbose(false) { };
		foo(value_type src, const bool verbose = false) : value(src), _verbose(verbose) { };
		foo(foo const &src, const bool verbose = false) : value(src.value), _verbose(verbose) { };
		~foo(void) { if (this->_verbose) std::cout << "~foo::foo()" << std::endl; };
		
		void m(void)
		{
			std::cout << "foo::m called [" << this->value << "]" << std::endl;
		};
		
		void m(void) const 
		{
			std::cout << "foo::m const called [" << this->value << "]" << std::endl;
		};
		
		
		foo &operator=(value_type src) { this->value = src; return *this; };
		foo &operator=(foo const &src) {
			if (this->_verbose || src._verbose)
				std::cout << "foo::operator=(foo) CALLED" << std::endl;
			this->value = src.value;
			return *this;
		};
		value_type	getValue(void) const { return this->value; };
		void		switchVerbose(void) { this->_verbose = !(this->_verbose); };

		operator value_type(void) const {
			return value_type(this->value);
		}
	private:
		value_type	value;
		bool		_verbose;
};

#include "map.hpp"

int main(void)
{
	/*
	ft::vector<int>	a(44);
	typename ft::vector<int>::iterator it = a.begin();

	out it << nl;
*/
	/*
	{
		ft::vector<int> vct(4);
		ft::vector<int> vct2(4);

		cmp(vct, vct);	// 0
		cmp(vct, vct2); // 1

		vct2.resize(10);

		cmp(vct, vct2); // 2


		
		cmp(vct2, vct); // 3

		vct[2] = 42;

		cmp(vct, vct2); // 4
		cmp(vct2, vct); // 5

		swap(vct, vct2);

		cmp(vct, vct2); // 6
		cmp(vct2, vct); // 7
	}

	out nl << nl;

	{
		std::vector<int> vct(4);
		std::vector<int> vct2(4);

		cmp(vct, vct);	// 0
		cmp(vct, vct2); // 1

		vct2.resize(10);

		cmp(vct, vct2); // 2
		cmp(vct2, vct); // 3

		vct[2] = 42;

		cmp(vct, vct2); // 4
		cmp(vct2, vct); // 5

		swap(vct, vct2);

		cmp(vct, vct2); // 6
		cmp(vct2, vct); // 7
	}*/
	/*
	{
		const int size = 5;
		ft::vector<int> vct(size);
		ft::vector<int>::reverse_iterator it = vct.rbegin();
		ft::vector<int>::const_reverse_iterator ite = vct.rbegin();

		for (int i = 0; i < size; ++i)
			it[i] = (size - i) * 5;

		it = it + 5;
		it = 1 + it;
		it = it - 4;
		std::cout << *(it += 2) << std::endl;
		std::cout << *(it -= 1) << std::endl;

		*(it -= 2) = 42;
		*(it += 2) = 21;

		std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

		std::cout << "(it == const_it): " << (ite == it) << std::endl;
		std::cout << "(const_ite - it): " << (ite - it) << std::endl;
		std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

		printSize(vct, true);
	}

	out nl << nl;

	{
		const int size = 5;
		std::vector<int> vct(size);
		std::vector<int>::reverse_iterator it = vct.rbegin();
		std::vector<int>::const_reverse_iterator ite = vct.rbegin();

		for (int i = 0; i < size; ++i)
			it[i] = (size - i) * 5;

		it = it + 5;
		it = 1 + it;
		it = it - 4;
		std::cout << *(it += 2) << std::endl;
		std::cout << *(it -= 1) << std::endl;

		*(it -= 2) = 42;
		*(it += 2) = 21;

		std::cout << "const_ite +=/-=: " << *(ite += 2) << " | " << *(ite -= 2) << std::endl;

		std::cout << "(it == const_it): " << (ite == it) << std::endl;
		std::cout << "(const_ite - it): " << (ite - it) << std::endl;
		std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

		printSize(vct, true);
	}
*/	/*
	{
		const int size = 5;
		ft::vector<foo<int>> vct(size);
		ft::vector<foo<int>>::reverse_iterator it(vct.rbegin());
		ft::vector<foo<int>>::const_reverse_iterator ite(vct.rend());

		for (int i = 1; it != ite; ++i)
			*it++ = (i * 7);
		printSize(vct, 1);

		it = vct.rbegin();
		ite = vct.rbegin();

		std::cout << *(++ite) << std::endl;
		std::cout << *(ite++) << std::endl;
		std::cout << *ite++ << std::endl;
		std::cout << *++ite << std::endl;

		it->m();
		ite->m();

		std::cout << *(++it) << std::endl;
		std::cout << *(it++) << std::endl;
		std::cout << *it++ << std::endl;
		std::cout << *++it << std::endl;

		std::cout << *(--ite) << std::endl;
		std::cout << *(ite--) << std::endl;
		std::cout << *--ite << std::endl;
		std::cout << *ite-- << std::endl;

		(*it).m();
		(*ite).m();
  
		std::cout << *(--it) << std::endl;
		std::cout << *(it--) << std::endl;
		std::cout << *it-- << std::endl;
		std::cout << *--it << std::endl;
	} */
/*	{
		const int size = 5;
		std::vector<foo<int>> vct(size);
		std::vector<foo<int>>::reverse_iterator it(vct.rbegin());
		std::vector<foo<int>>::const_reverse_iterator ite(vct.rend());

		for (int i = 1; it != ite; ++i)
			*it++ = (i * 7);
		printSize(vct, 1);

		it = vct.rbegin();
		ite = vct.rbegin();

		std::cout << *(++ite) << std::endl;
		std::cout << *(ite++) << std::endl;
		std::cout << *ite++ << std::endl;
		std::cout << *++ite << std::endl;

		it->m();
		ite->m();

		std::cout << *(++it) << std::endl;
		std::cout << *(it++) << std::endl;
		std::cout << *it++ << std::endl;
		std::cout << *++it << std::endl;

		std::cout << *(--ite) << std::endl;
		std::cout << *(ite--) << std::endl;
		std::cout << *--ite << std::endl;
		std::cout << *ite-- << std::endl;

		(*it).m();
		(*ite).m();
  
		std::cout << *(--it) << std::endl;
		std::cout << *(it--) << std::endl;
		std::cout << *it-- << std::endl;
		std::cout << *--it << std::endl;
	}*/
	/*
	{
		const int size = 5;
		ft::vector<int> vct(size);
		ft::vector<int>::iterator it_ = vct.begin();
		ft::vector<int>::reverse_iterator it(it_);

		for (int i = 0; i < size; ++i)
			vct[i] = (i + 1) * 5;
		printSize(vct);

		std::cout << (it_ == it.base()) << std::endl;
		std::cout << (it_ == (it + 3).base()) << std::endl;

		std::cout << *(it.base() + 1) << std::endl;
		std::cout << *(it - 3) << std::endl;
		std::cout << *(it - 3).base() << std::endl;
		it -= 3;
		std::cout << *it.base() << std::endl;

		std::cout << "TEST OFFSET" << std::endl;
		std::cout << *(it) << std::endl;
		std::cout << *(it).base() << std::endl;
		std::cout << *(it - 0) << std::endl;
		std::cout << *(it - 0).base() << std::endl;
		std::cout << *(it - 1).base() << std::endl;
	}
	out nl << nl << nl;
	{
		const int size = 5;
		std::vector<int> vct(size);
		std::vector<int>::iterator it_ = vct.begin();
		std::vector<int>::reverse_iterator it(it_);

		for (int i = 0; i < size; ++i)
			vct[i] = (i + 1) * 5;
		printSize(vct);

		std::cout << (it_ == it.base()) << std::endl;
		std::cout << (it_ == (it + 3).base()) << std::endl;

		std::cout << *(it.base() + 1) << std::endl;
		std::cout << *(it - 3) << std::endl;
		std::cout << *(it - 3).base() << std::endl;
		it -= 3;
		std::cout << *it.base() << std::endl;

		std::cout << "TEST OFFSET" << std::endl;
		std::cout << *(it) << std::endl;
		std::cout << *(it).base() << std::endl;
		std::cout << *(it - 0) << std::endl;
		std::cout << *(it - 0).base() << std::endl;
		std::cout << *(it - 1).base() << std::endl;
	}
*/	/*
	{
		const int start_size = 7;
		ft::vector<int> vct(start_size, 20);
		ft::vector<int> vct2;
		ft::vector<int>::iterator it = vct.begin();

		for (int i = 2; i < start_size; ++i)
			it[i] = (start_size - i) * 3;
		printSize(vct, true);

		vct.resize(10, 42);
		printSize(vct, true);

		vct.resize(18, 43);
		printSize(vct, true);
		vct.resize(10);
		printSize(vct, true);
		vct.resize(23, 44);
		printSize(vct, true);
		vct.resize(5);
		printSize(vct, true);
		vct.reserve(5);
		vct.reserve(3);
		printSize(vct, true);
		vct.resize(87);
		vct.resize(5);
		printSize(vct, true);

		is_empty(vct2);
		vct2 = vct;
		is_empty(vct2);
		vct.reserve(vct.capacity() + 1);
		printSize(vct, true);
		printSize(vct2, true);

		vct2.resize(0);
		is_empty(vct2);
		printSize(vct2, true);
	}
	out nl << nl;
	{
		const int start_size = 7;
		std::vector<int> vct(start_size, 20);
		std::vector<int> vct2;
		std::vector<int>::iterator it = vct.begin();

		for (int i = 2; i < start_size; ++i)
			it[i] = (start_size - i) * 3;
		printSize(vct, true);

		vct.resize(10, 42);
		printSize(vct, true);

		vct.resize(18, 43);
		printSize(vct, true);
		vct.resize(10);
		printSize(vct, true);
		vct.resize(23, 44);
		printSize(vct, true);
		vct.resize(5);
		printSize(vct, true);
		vct.reserve(5);
		vct.reserve(3);
		printSize(vct, true);
		vct.resize(87);
		vct.resize(5);
		printSize(vct, true);

		is_empty(vct2);
		vct2 = vct;
		is_empty(vct2);
		vct.reserve(vct.capacity() + 1);
		printSize(vct, true);
		printSize(vct2, true);

		vct2.resize(0);
		is_empty(vct2);
		printSize(vct2, true);
	}*/
	/*
	{
		ft::vector<int> vct(4);
		ft::vector<int> vct2(4);

		cmp(vct, vct);  // 0
		cmp(vct, vct2); // 1

		vct2.resize(10);

		cmp(vct, vct2); // 2
		cmp(vct2, vct); // 3

		vct[2] = 42;

		cmp(vct, vct2); // 4
		cmp(vct2, vct); // 5

		swap(vct, vct2);

		cmp(vct, vct2); // 6
		cmp(vct2, vct); // 7

	}
	out nl << nl;
{
		std::vector<int> vct(4);
		std::vector<int> vct2(4);

		cmp(vct, vct);  // 0
		cmp(vct, vct2); // 1

		vct2.resize(10);

		cmp(vct, vct2); // 2
		cmp(vct2, vct); // 3

		vct[2] = 42;

		cmp(vct, vct2); // 4
		cmp(vct2, vct); // 5

		swap(vct, vct2);

		cmp(vct, vct2); // 6
		cmp(vct2, vct); // 7

	}
*/
/*	{
		std::vector<std::string> vct(8);
		std::vector<std::string> vct2;
		std::vector<std::string>::iterator it = vct.begin();

		for (unsigned long int i = 0; i < vct.size(); ++i)
		{
			it[i] = std::string((vct.size() - i), i + 65);
		}
		out nl;
		printSize(vct, true);

		std::cout << "push_back():\n"
				  << std::endl;

		vct.push_back("One long string");
		vct2.push_back("Another long string");

		printSize(vct);
		printSize(vct2);

		vct.pop_back();
		vct2.pop_back();

		printSize(vct);
		printSize(vct2);

		return (0);
	} */
/*	{
		ft::vector<std::string> vct(8);
		ft::vector<std::string> vct2;
		ft::vector<std::string>::iterator it = vct.begin();

		for (unsigned long int i = 0; i < vct.size(); ++i)
		{
			it[i] = std::string((vct.size() - i), i + 65);
		}
		out nl;
		printSize(vct, true);

		std::cout << "push_back():\n"
				  << std::endl;

		vct.push_back("One long string");
		vct2.push_back("Another long string");

		printSize(vct);
		printSize(vct2);

		vct.pop_back();
		vct2.pop_back();

		printSize(vct);
		printSize(vct2);

		return (0);
	} */
	/*
		{
			 ft::vector<int> vct(7);

			 for (unsigned long int i = 0; i < vct.size(); ++i)
			 {
					 vct.at(i) = (vct.size() - i) * 3;
					 std::cout << "vct[]: " << vct[i] << std::endl;
			 }
			 printSize(vct);

			 ft::vector<int> const vct_c(vct);

			 std::cout << "front(): " << vct.front() << " " << vct_c.front() << std::endl;
			 std::cout << "back(): " << vct.back() << " " <<  vct_c.back() << std::endl;

			 for (unsigned long int i = 0; i < vct_c.size(); ++i)
					 std::cout << "vct_c.at(): " << vct_c.at(i) << std::endl;
			 try {
					 std::cout << vct_c.at(10) << std::endl;
			 }
			 catch (std::out_of_range &e) {
					 std::cout << "Catch out_of_range exception!" << std::endl;
			 }
			 catch (std::exception &e) {
					 std::cout << "Catch exception: " << e.what() << std::endl;
			 }
			 printSize(vct_c);
			 return (0);
	}
	 */
	/*
		{
			const int size = 5;
			ft::vector<int> vct(size);
			ft::vector<int>::iterator it_0(vct.begin());
			ft::vector<int>::iterator it_1(vct.end());
			ft::vector<int>::iterator it_mid;

			ft::vector<int>::const_iterator cit_0 = vct.begin();
			ft::vector<int>::const_iterator cit_1;
			ft::vector<int>::const_iterator cit_mid;

			for (int i = size; it_0 != it_1; --i)
				*it_0++ = i;
			printSize(vct, 1);
			it_0 = vct.begin();
			cit_1 = vct.end();
			it_mid = it_0 + 3;
			cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;

			std::cout << std::boolalpha;
			std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;

			std::cout << "\t\tft_eq_ope:" << std::endl;
			// regular it
			ft_eq_ope(it_0 + 3, it_mid);
			ft_eq_ope(it_0, it_1);
			ft_eq_ope(it_1 - 3, it_mid);
			// const it
			ft_eq_ope(cit_0 + 3, cit_mid);
			ft_eq_ope(cit_0, cit_1);
			ft_eq_ope(cit_1 - 3, cit_mid);
			// both it
			ft_eq_ope(it_0 + 3, cit_mid);
			ft_eq_ope(it_mid, cit_0 + 3);
			ft_eq_ope(it_0, cit_1);
			ft_eq_ope(it_1, cit_0);
			ft_eq_ope(it_1 - 3, cit_mid);
			ft_eq_ope(it_mid, cit_1 - 3);

		}

		{
			const int size = 5;
			std::vector<int> vct(size);
			std::vector<int>::iterator it_0(vct.begin());
			std::vector<int>::iterator it_1(vct.end());
			std::vector<int>::iterator it_mid;

			std::vector<int>::const_iterator cit_0 = vct.begin();
			std::vector<int>::const_iterator cit_1;
			std::vector<int>::const_iterator cit_mid;

			for (int i = size; it_0 != it_1; --i)
				*it_0++ = i;
			printSize(vct, 1);
			it_0 = vct.begin();
			cit_1 = vct.end();
			it_mid = it_0 + 3;
			cit_mid = it_0 + 3; cit_mid = cit_0 + 3; cit_mid = it_mid;

	//		std::cout << std::boolalpha;
			std::cout << ((it_0 + 3 == cit_0 + 3) && (cit_0 + 3 == it_mid)) << std::endl;

			std::cout << "\t\tft_eq_ope:" << std::endl;
			// regular it
			ft_eq_ope(it_0 + 3, it_mid);
			ft_eq_ope(it_0, it_1);
			ft_eq_ope(it_1 - 3, it_mid);
			// const it
			ft_eq_ope(cit_0 + 3, cit_mid);
			ft_eq_ope(cit_0, cit_1);
			ft_eq_ope(cit_1 - 3, cit_mid);
			// both it
			ft_eq_ope(it_0 + 3, cit_mid);
			ft_eq_ope(it_mid, cit_0 + 3);
			ft_eq_ope(it_0, cit_1);
			ft_eq_ope(it_1, cit_0);
			ft_eq_ope(it_1 - 3, cit_mid);
			ft_eq_ope(it_mid, cit_1 - 3);

		}
	*/
	/*
		{
			ft::vector<int>	a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
			ft::vector<int> b = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
			ft::vector<int> c = b;


			if (a <= b)
				out "youhou" << nl;
	*/
	/*
			a.erase(a.begin() + 8, a.begin() + 12);
			out a.size() << " " << a.capacity() << nl;
			out *(a.end() - 1) << nl;
			ftVCout(a);

			a.resize(34);
			out a.size() << " " << a.capacity() << nl;
			out *(a.end() - 1) << nl;

			a.insert(a.begin() + 4, b.begin(), b.begin() + 7);

			ftVCout(a);
	*/

	//		out nl;

	//		b.erase(b.begin(), b.end() - 1);
	//		out b.size() << " " << b.capacity() << nl;
	//		out *(b.end() - 1) << nl;
	//		ftVCout(b);
	/*	}
			out nl << nl;
		{
			std::vector<int>	a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
			std::vector<int> b = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

	//		a.erase(a.begin() + 8, a.begin() + 12);
	//		out a.size() << " " << a.capacity() << nl;
	//		out *(a.end() - 1) << nl;
	//		ftVCout(a);

			a.resize(34);
			out a.size() << " " << a.capacity() << nl;
			out *(a.end() - 1) << nl;
			ftVCout(a);



	//		out nl;
	//
	//		b.erase(b.begin(), b.end() - 1);
	//		out b.size() << " " << b.capacity() << nl;
	//		out *(b.end() - 1) << nl;
	//		ftVCout(b);
	//		b.pop_back();
	//		ftVCout(b);
	//		b.pop_back();
	//		ftVCout(b);
	//		b.pop_back();
	//		ftVCout(b);
		}
	*/
	/*
		{
			ft::vector<int>	a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
			ft::vector<int> b = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

			typename ft::random_access_iterator<int> rai = a.insert(a.begin() + 4, 5, -1) - 1;

			out "ret = " << *(a.insert(a.begin() + 4, 5, -1) - 1) << nl;
			ftVCout(a);
			out a.capacity() << " " << a.size() << nl;
	//		a.reserve(50);
			ftVCout(a);
			out a.capacity() << " ! " << a.size() << nl;
			out "ret = " << *(a.insert(a.begin() + 8, 3, -2) - 1) << nl;
			ftVCout(a);
			out a.capacity() << " " << a.size() << nl;

			out nl;

			a.insert(a.begin() + 8, b.begin() + 8, b.begin() + 11);
			out a.capacity() << " ! " << a.size() << nl;
			ftVCout(a);

			a.reserve(50);
			a.insert(a.begin() + 2, b.begin() + 2, b.begin() + 10);
			out a.capacity() << " ! " << a.size() << nl;
			ftVCout(a);
		}
			out nl << nl;
		{
			std::vector<int>	a = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
			std::vector<int> b = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

			out "ret = " << *(a.insert(a.begin() + 4, 5, -1) - 1) << nl;
			ftVCout(a);
			out a.capacity() << " " << a.size() << nl;
			a.reserve(50);
			ftVCout(a);
			out a.capacity() << " ! " << a.size() << nl;
			out "ret = " << *(a.insert(a.begin() + 8, 3, -2) - 1) << nl;
			ftVCout(a);
			out a.capacity() << " " << a.size() << nl;

			out nl;

			a.insert(a.begin() + 8, b.begin() + 8, b.begin() + 11);
			out a.capacity() << " ! " << a.size() << nl;
			ftVCout(a);

			a.reserve(50);
			a.insert(a.begin() + 2, b.begin() + 2, b.begin() + 10);
			out a.capacity() << " ! " << a.size() << nl;
			ftVCout(a);
		}
	*/
	/*	{

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
		}*/
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
	*/
	/*
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
