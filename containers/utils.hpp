#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{
	template <class Ite1, class Ite2>
	bool	equal(Ite1 first1, Ite1 last1, Ite2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return false;
			++first1; ++first2;
		}
		return true;
	}

	template <class Ite1, class Ite2>
	bool	lexicographical_compare(Ite1 first1, Ite1 last1, Ite2 first2, Ite2 last2)
	{
		while (first1 != last1 && first2 != last2 && *first1 == *first2)
		{
			++first1;
			++first2;
		}
		if (first1 == last1)
			return (first2 != last2);
		else if (first2 == last2)
			return (false);
		return (*first1 < *first2);
	}

	template <class T1, class T2>
	struct pair
	{
		T1	first;
		T2	second;

		pair(): first(), second() {}

		template <class U, class V>
		pair(const pair<U, V> &pr): first(pr.first), second(pr.second) {}
		pair(const T1& a, const T2& b): first(a), second(b) {}

		pair &operator=(const pair &pr)
		{
			if (*this == pr)
				return (*this);

			this->first = pr.first;
			this->second = pr.second;

			return (*this);
		}

		virtual ~pair() {}
	};

	template <class T1, class T2>
	bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{ return (lhs.first == rhs.first && lhs.second == rhs.second); }

	template <class T1, class T2>
	bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{ return !(lhs == rhs); }

	template <class T1, class T2>
	bool operator<(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{ return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); }

	template <class T1, class T2>
	bool operator<=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{ return !(rhs < lhs); }

	template <class T1, class T2>
	bool operator>(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{ return (rhs < lhs); }

	template <class T1, class T2>
	bool operator>=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{ return !(lhs < rhs); }

	template <class T1, class T2>
	ft::pair<T1, T2>	make_pair(T1 x, T2 y)
		{ return (ft::pair<T1, T2>(x, y)); }

} // namespace ft

#endif
