#ifndef BIDIRECTIONAL_ITERATOR_HPP
# define BIDIRECTIONAL_ITERATOR_HPP

namespace ft
{
	class bidirectional_iterator_tag { };

	template<typename T, class Distance = __PTRDIFF_TYPE__>
	class bidirectional_iterator
	{
		public :

			typedef T								value_type;
			typedef Distance						difference_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;
			typedef ft::bidirectional_iterator_tag	iterator_category;

		// CONSTRUCT DESTRUCT COPY EQUAL----------------------------------------------------
			bidirectional_iterator(void) : _elem(nullptr) {}
			bidirectional_iterator(pointer elem) : _elem(elem) {}
			bidirectional_iterator(const bidirectional_iterator &src) : _elem(src._elem) {}

			bidirectional_iterator	&operator=(const bidirectional_iterator &src)
			{
				if (this == &src)
					return (*this);
				this->_elem = src._elem;
				return (*this);
			}

			// const declaration
			operator bidirectional_iterator<const value_type>() const
				{ return (bidirectional_iterator<const value_type>(this->_elem)); }

			virtual ~bidirectional_iterator() {}

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
			bidirectional_iterator 				&operator++(void)
			{
				this->_elem++;
				return (*this);
			}
			bidirectional_iterator				operator++(int)
			{
				bidirectional_iterator randtmp(*this);
				operator++();
				return (randtmp);
			}
			bidirectional_iterator				&operator--(void)
			{
				this->_elem--;
				return (*this);
			}
			bidirectional_iterator				operator--(int)
			{
				bidirectional_iterator randtmp(*this);
				operator--();
				return (randtmp);
			}
			//math
			bidirectional_iterator				operator+(const difference_type n) const
				{ return (this->_elem + n); }
			bidirectional_iterator				operator-(const difference_type n) const
				{ return (this->_elem - n); }
			difference_type						operator-(const bidirectional_iterator &it) const
				{ return (this->_elem - it._elem); }
			bidirectional_iterator				&operator+=(const difference_type n)
			{
				this->_elem += n;
				return (*this);
			}
			bidirectional_iterator				&operator-=(const difference_type n)
			{
				this->_elem -= n;
				return (*this);
			}

			//comparison
			bool						operator!=(const bidirectional_iterator it) const
				{ return (this->_elem != it._elem); }
			bool						operator==(const bidirectional_iterator it) const
				{ return (this->_elem == it._elem); }
			bool						operator<(const bidirectional_iterator it) const
				{ return (this->_elem < it._elem); }
			bool						operator>(const bidirectional_iterator it) const
				{ return (this->_elem > it._elem); }
			bool						operator<=(const bidirectional_iterator it) const
				{ return (this->_elem <= it._elem); }
			bool						operator>=(const bidirectional_iterator it) const
				{ return (this->_elem >= it._elem); }

			// [pos]
			reference							operator[](difference_type n)
				{ return (*(this->_elem + n)); }

			// cout
			friend	std::ostream	&operator<<
				(std::ostream &os, bidirectional_iterator const &it)
				{ return (os << it._elem); }

		private:
			pointer	_elem;

	}; // class bidirectional_iterator

// CONST ITERATOR OVERLOADS
	template<typename T_L, typename T_R>
	bool	operator==(const ft::bidirectional_iterator<T_L> lit,
			  const ft::bidirectional_iterator<T_R> rit)
	{
		return (lit.base() == rit.base());
	}

	template<typename T_L, typename T_R>
	bool	operator!=(const ft::bidirectional_iterator<T_L> lit,
			  const ft::bidirectional_iterator<T_R> rit)
	{
		return (lit.base() != rit.base());
	}

	template<typename T_L, typename T_R>
	bool	operator<(const ft::bidirectional_iterator<T_L> lit,
			  const ft::bidirectional_iterator<T_R> rit)
	{
		return (lit.base() < rit.base());
	}

	template<typename T_L, typename T_R>
	bool	operator>(const ft::bidirectional_iterator<T_L> lit,
			  const ft::bidirectional_iterator<T_R> rit)
	{
		return (lit.base() > rit.base());
	}

	template<typename T_L, typename T_R>
	bool	operator<=(const ft::bidirectional_iterator<T_L> lit,
			  const ft::bidirectional_iterator<T_R> rit)
	{
		return (lit.base() <= rit.base());
	}

	template<typename T_L, typename T_R>
	bool	operator>=(const ft::bidirectional_iterator<T_L> lit,
			  const ft::bidirectional_iterator<T_R> rit)
	{
		return (lit.base() >= rit.base());
	}

	template<typename T>
	typename ft::bidirectional_iterator<T>
	operator+(const typename ft::bidirectional_iterator<T>::difference_type &n,
				const ft::bidirectional_iterator<T> it)
	{
		return (it + n);
	}

	template<typename T_L, typename T_R>
	typename ft::bidirectional_iterator<T_L>::difference_type
	operator-(const ft::bidirectional_iterator<T_L> lit,
			  const ft::bidirectional_iterator<T_R> rit)
	{
		return (lit.base() - rit.base());
	}

	template<typename T>
	typename ft::bidirectional_iterator<T>
	operator-(const typename ft::bidirectional_iterator<T>::difference_type &n,
				const ft::bidirectional_iterator<T> it)
	{
		return (it - n);
	}

} // namespace ft

#endif
