#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP

namespace ft
{
	class random_access_iterator_tag { };

	template<class Category, class T, class Distance = __PTRDIFF_TYPE__>
	class iterator
	{
		public :
			typedef T		value_type;
			typedef Distance	difference_type;
			typedef value_type*	pointer;
			typedef value_type&	reference;
			typedef Category	iterator_category;
	}; // class iterator

	template<typename T>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	{
		public :
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>
						::iterator_category                                 iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>
						::value_type                                        value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>
						::difference_type                                   difference_type;
			typedef T*	                                                    pointer;
			typedef T&	                                                    reference;


		// CONSTRUCT DESTRUCT COPY EQUAL----------------------------------------------------
			random_access_iterator(void) : _elem(nullptr) {}

			random_access_iterator(pointer elem) : _elem(elem) {}

			random_access_iterator(const random_access_iterator &src) : _elem(src._elem) {}

			random_access_iterator &operator=(const random_access_iterator &src)
			{
				if (this == &src)
					return (*this);
				this->_elem = src._elem;
				return (*this);
			}
			// const declaration
			operator random_access_iterator<const T>() const
			{
				return (random_access_iterator<const T>(this->_elem));
			}

			virtual ~random_access_iterator() {}


		// GETTER
			pointer get_elem() const
			{ return (this->_elem); }


		// OVERLOADS
			//pointer
			reference							operator*(void) const
				{ return (*this->_elem); }

			pointer 							operator->(void)
				{ return &(this->operator*()); }


			//increment decrement
			random_access_iterator 				&operator++(void)
			{
				_elem++;
				return (*this);
			}

			random_access_iterator				operator++(int)
			{
				random_access_iterator rtn(*this);
				operator++();
				return (rtn);
			}

			random_access_iterator				&operator--(void)
			{
				_elem--;
				return (*this);
			}

			random_access_iterator				operator--(int)
			{
				random_access_iterator rtn(*this);
				operator--();
				return (rtn);
			}

			//math
			random_access_iterator				operator+(const difference_type n) const
				{ return (this->_elem + n); }

			difference_type						operator+(const random_access_iterator &it)
				{ return (this->_elem + it.elem); }

			random_access_iterator				operator-(const difference_type n) const
				{ return (this->_elem - n); }

			difference_type				operator-(const random_access_iterator &it)
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
			difference_type						operator!=(const random_access_iterator it)
				{ return (this->_elem != it._elem); }

			difference_type						operator==(const random_access_iterator &it)
				{ return (this->_elem == it._elem); }

			difference_type						operator<(const random_access_iterator &it)
				{ return (this->_elem < it._elem); }

			difference_type						operator>(const random_access_iterator &it)
				{ return (this->_elem > it._elem); }

			difference_type						operator<=(const random_access_iterator &it)
				{ return (this->_elem <= it._elem); }

			difference_type						operator>=(const random_access_iterator &it)
				{ return (this->_elem >= it._elem); }

			// [pos]
			reference							operator[](difference_type n)
				{ return (*(operator+(n))); }

			// cout
			friend	std::ostream	&operator<<
				(std::ostream &os, random_access_iterator const &it)
				{ return (os << it._elem); }

		private:
			pointer	_elem;

	}; // class random_access_iterator

// CONST ITERATOR OVERLOADS

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator==(const ft::random_access_iterator<T_L> lit,
			  const ft::random_access_iterator<T_R> rit)
	{
		return (lit.get_elem() == rit.get_elem());
	}

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator!=(const ft::random_access_iterator<T_L> lit,
			  const ft::random_access_iterator<T_R> rit)
	{
		return (lit.get_elem() != rit.get_elem());
	}

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator<(const ft::random_access_iterator<T_L> lit,
			  const ft::random_access_iterator<T_R> rit)
	{
		return (lit.get_elem() < rit.get_elem());
	}

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator>(const ft::random_access_iterator<T_L> lit,
			  const ft::random_access_iterator<T_R> rit)
	{
		return (lit.get_elem() > rit.get_elem());
	}

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator<=(const ft::random_access_iterator<T_L> lit,
			  const ft::random_access_iterator<T_R> rit)
	{
		return (lit.get_elem() <= rit.get_elem());
	}

	template<typename T_L,
			 typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator>=(const ft::random_access_iterator<T_L> lit,
			  const ft::random_access_iterator<T_R> rit)
	{
		return (lit.get_elem() >= rit.get_elem());
	}

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator+(const ft::random_access_iterator<T_L> lit,
			const ft::random_access_iterator<T_R> rit)
	{
		return (lit.get_elem() + rit.get_elem());
	}

	template<typename T_L, typename T_R>
	typename ft::random_access_iterator<T_L>::difference_type
	operator-(const ft::random_access_iterator<T_L> lit,
			  const ft::random_access_iterator<T_R> rit)
	{
		return (lit.get_elem() - rit.get_elem());
	}

} // namespace ft

#endif