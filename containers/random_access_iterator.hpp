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
	};

	template<typename T>
	class random_access_iterator : ft::iterator<ft::random_access_iterator_tag, T>
	{
		public :
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>
						::iterator_category
				iterator_category;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>
						::value_type	
				value_type;
			typedef typename ft::iterator<ft::random_access_iterator_tag, T>
						::difference_type
				difference_type;
			typedef T*	pointer;
			typedef T&	reference;


		// CONSTRUCT DESTRUCT -------------------------------------------------------
			random_access_iterator(void)
				{ this->_elem = NULL; }
			random_access_iterator(pointer elem)
				{ this->_elem = elem; }
			random_access_iterator(const random_access_iterator &src)
				{ this->_elem = src._elem; }


		// OVERLOADS -----------------------------------------------------------------
			friend	std::ostream	&operator<<
				(std::ostream &os, ft::random_access_iterator<T> const &it)
				{ return (os << it._elem); }

			T	operator*()
				{ return (*this->_elem); }

			random_access_iterator	operator+(difference_type const n)
				{ return (this->_elem + n); }

			pointer base() const
				{ return (this->_elem); }

			random_access_iterator& operator++(void)
			{
				_elem++;
				return (*this);
			}

			random_access_iterator operator++(int)
			{
				random_access_iterator rtn(*this);
				operator++();
				return (rtn);
			}

			template <typename U>
			difference_type	operator!=(const ft::random_access_iterator<U> rhs)
				{ return (this->_elem != rhs.base()); }

			/* For iterator != const_iterator */
			template<typename T_L, typename T_R>
			difference_type	operator!=(const ft::random_access_iterator<T_R> rhs)
				{ return (this->_elem != rhs.base()); }
		//-----------------------------------------------------------------------------


		private :
			pointer	_elem;
	};
}

#endif

