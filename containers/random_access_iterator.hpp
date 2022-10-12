#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

namespace ft
{
	class random_access_iterator_tag { };

	template<typename T, class Distance = __PTRDIFF_TYPE__>
	class random_access_iterator
	{
		public :

			typedef T								value_type;
			typedef Distance						difference_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;
			typedef ft::random_access_iterator_tag	iterator_category;

		// CONSTRUCT DESTRUCT COPY EQUAL----------------------------------------------------
			random_access_iterator(void) : _elem(nullptr) {}
			random_access_iterator(pointer elem) : _elem(elem) {}
			random_access_iterator(const random_access_iterator &src) : _elem(src._elem) {}

			random_access_iterator	&operator=(const random_access_iterator &src)
			{
				if (this == &src)
					return (*this);
				this->_elem = src._elem;
				return (*this);
			}

			// const declaration
			operator random_access_iterator<const value_type>() const
				{ return (random_access_iterator<const value_type>(this->_elem)); }

			virtual ~random_access_iterator() {}

		// GETTER
			pointer base() const
			{ return (this->_elem); }

		// OVERLOADS
			//pointer
			reference							operator*(void) const
				{ return (*this->_elem); }
			pointer 							operator->(void) const
				{ return &(this->operator*()); }

			//increment decrement
			random_access_iterator 				&operator++(void)
			{
				this->_elem++;
				return (*this);
			}
			random_access_iterator				operator++(int)
			{
				random_access_iterator randtmp(*this);
				operator++();
				return (randtmp);
			}
			random_access_iterator				&operator--(void)
			{
				this->_elem--;
				return (*this);
			}
			random_access_iterator				operator--(int)
			{
				random_access_iterator randtmp(*this);
				operator--();
				return (randtmp);
			}
			//math
			random_access_iterator				operator+(const difference_type n) const
				{ return (this->_elem + n); }
			random_access_iterator				operator-(const difference_type n) const
				{ return (this->_elem - n); }
			difference_type						operator-(const random_access_iterator &it) const
				{ return (this->_elem - it._elem); }
			random_access_iterator				&operator+=(const difference_type n)
			{
				this->_elem += n;
				return (*this);
			}
			random_access_iterator				&operator-=(const difference_type n)
			{
				this->_elem -= n;
				return (*this);
			}

			//comparison
			bool						operator!=(const random_access_iterator it) const
				{ return (this->_elem != it._elem); }
			bool						operator==(const random_access_iterator it) const
				{ return (this->_elem == it._elem); }
			bool						operator<(const random_access_iterator it) const
				{ return (this->_elem < it._elem); }
			bool						operator>(const random_access_iterator it) const
				{ return (this->_elem > it._elem); }
			bool						operator<=(const random_access_iterator it) const
				{ return (this->_elem <= it._elem); }
			bool						operator>=(const random_access_iterator it) const
				{ return (this->_elem >= it._elem); }

			// [pos]
			reference							operator[](difference_type n)
				{ return (*(this->_elem + n)); }

			// cout
			friend	std::ostream	&operator<<
				(std::ostream &os, random_access_iterator const &it)
				{ return (os << it._elem); }

		private:
			pointer	_elem;

	}; // class random_access_iterator

// CONST ITERATOR OVERLOADS
	template<typename T_L, typename T_R>
	//typename ft::random_access_iterator<T_L>::difference_type
	bool	operator==(const ft::random_access_iterator<T_L> lit,
			  const ft::random_access_iterator<T_R> rit)
	{
		return (lit.base() == rit.base());
	}

	template<typename T_L, typename T_R>
//	typename ft::random_access_iterator<T_L>::difference_type
	bool	operator!=(const ft::random_access_iterator<T_L> lit,
			  const ft::random_access_iterator<T_R> rit)
	{
		return (lit.base() != rit.base());
	}

	template<typename T_L, typename T_R>
//	typename ft::random_access_iterator<T_L>::difference_type
	bool	operator<(const ft::random_access_iterator<T_L> lit,
			  const ft::random_access_iterator<T_R> rit)
	{
		return (lit.base() < rit.base());
	}

	template<typename T_L, typename T_R>
//	typename ft::random_access_iterator<T_L>::difference_type
	bool	operator>(const ft::random_access_iterator<T_L> lit,
			  const ft::random_access_iterator<T_R> rit)
	{
		return (lit.base() > rit.base());
	}

	template<typename T_L, typename T_R>
//	typename ft::random_access_iterator<T_L>::difference_type
	bool	operator<=(const ft::random_access_iterator<T_L> lit,
			  const ft::random_access_iterator<T_R> rit)
	{
		return (lit.base() <= rit.base());
	}

	template<typename T_L, typename T_R>
//	typename ft::random_access_iterator<T_L>::difference_type
	bool	operator>=(const ft::random_access_iterator<T_L> lit,
			  const ft::random_access_iterator<T_R> rit)
	{
		return (lit.base() >= rit.base());
	}

	template<typename T>
	typename ft::random_access_iterator<T>
	operator+(const typename ft::random_access_iterator<T>::difference_type &n,
				const ft::random_access_iterator<T> it)
	{
		return (it + n);
	}

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator-(const ft::random_access_iterator<T_L> lit,
			  const ft::random_access_iterator<T_R> rit)
	{
		return (lit.base() - rit.base());
	}

	template<typename T>
	typename ft::random_access_iterator<T>
	operator-(const typename ft::random_access_iterator<T>::difference_type &n,
				const ft::random_access_iterator<T> it)
	{
		return (it - n);
	}

} // namespace ft

#endif
