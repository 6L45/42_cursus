#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP

# include "random_access_iterator.hpp"

namespace ft
{
	class reverse_iterator_tag { };	

	template<typename T, class Distance = __PTRDIFF_TYPE__>
	class reverse_iterator
	{
		public :
			typedef	T							value_type;
			typedef	Distance					difference_type;
			typedef	value_type*					pointer;
			typedef	value_type&					reference;
			typedef	ft::reverse_iterator_tag	iterator_category;

		// CONSTRUCT DESTRUCT COPY EQUAL ----------------------------------------------
			reverse_iterator() : _elem(nullptr) {};
			reverse_iterator(pointer elem) : _elem(elem) {}
			reverse_iterator(const reverse_iterator &src) : _elem(src.base()) {}
			reverse_iterator(const ft::random_access_iterator<value_type> &it) : _elem(it.base()) {}

			reverse_iterator	&operator=(const reverse_iterator &src)
			{
				if (this == &src)
					return (*this);
				this->_elem = src._elem;
				return (*this);
			}
			// const declaration
			operator	reverse_iterator<const T>() const
				{ return (reverse_iterator<const T>(this->_elem)); }

			virtual	~reverse_iterator() {}

		//GETTER
			pointer	base() const
				{ return (this->_elem); }

		//OVERLOADS
			//pointer
			reference								operator*() const
            {
                pointer tmp = this->_elem;
                return (*(--tmp));
            }
			pointer 								operator->() const 
				{ return &(operator*()); }

			// increment decremment
			reverse_iterator &operator++()
			{
				--this->_elem;
				return (*this);
			}
			reverse_iterator operator++(int)
			{
				reverse_iterator tmp = *this;
				--this->_elem;
				return (tmp);
			}

			reverse_iterator &operator--()
			{
				++this->_elem;
				return (*this);
			}
			reverse_iterator operator--(int)
			{
				reverse_iterator tmp = *this;
				++this->_elem;
				return (tmp);
			}

			//math
			reverse_iterator			operator+(difference_type n) const
				{ return (this->_elem - n); }
			reverse_iterator			operator-(difference_type n) const
				{ return (this->_elem + n); }
			difference_type				operator-(const reverse_iterator &it) const
				{ return (this->_elem - it._elem); }

			reverse_iterator			&operator+=(difference_type n)
			{
				this->_elem -= n;
				return (*this);
			}
			reverse_iterator			&operator-=(difference_type n)
			{
				this->_elem += n;
				return (*this);
			}

			//comparison
			bool						operator!=(const reverse_iterator it) const
				{ return (this->_elem != it._elem); }
			bool						operator==(const reverse_iterator &it) const
				{ return (this->_elem == it._elem); }
			bool						operator<(const reverse_iterator &it) const
				{ return (this->_elem > it._elem); }
			bool						operator>(const reverse_iterator &it) const
				{ return (this->_elem < it._elem); }
			bool						operator<=(const reverse_iterator &it) const
				{ return (this->_elem >= it._elem); }
			bool						operator>=(const reverse_iterator &it) const
				{ return (this->_elem <= it._elem); }

			// [pos]
			reference					operator[](difference_type n)
				{ return (this->_elem[-n - 1]); }
			
			// cout
			friend	std::ostream		&operator<<
				(std::ostream &os, reverse_iterator const &it)
				{ return (os << it._elem); }

		private :
			pointer	_elem;

	}; // class reverse_iterator

	// CONST ITERATOR OVERLOADS
	template<typename T_L, typename T_R>
	bool	operator==(const ft::reverse_iterator<T_L> lit,
			  const ft::reverse_iterator<T_R> rit)
	{
		return (lit.base() == rit.base());
	}

	template<typename T_L, typename T_R>
	bool	operator!=(const ft::reverse_iterator<T_L> lit,
			  const ft::reverse_iterator<T_R> rit)
	{
		return (lit.base() != rit.base());
	}

	template<typename T_L, typename T_R>
	bool	operator<(const ft::reverse_iterator<T_L> lit,
			  const ft::reverse_iterator<T_R> rit)
	{
		return (lit.base() > rit.base());
	}

	template<typename T_L, typename T_R>
	bool	operator>(const ft::reverse_iterator<T_L> lit,
			  const ft::reverse_iterator<T_R> rit)
	{
		return (lit.base() < rit.base());
	}

	template<typename T_L, typename T_R>
	bool	operator<=(const ft::reverse_iterator<T_L> lit,
			  const ft::reverse_iterator<T_R> rit)
	{
		return (lit.base() >= rit.base());
	}

	template<typename T_L, typename T_R>
	bool	operator>=(const ft::reverse_iterator<T_L> lit,
			  const ft::reverse_iterator<T_R> rit)
	{
		return (lit.base() <= rit.base());
	}

	template<typename T>
	typename ft::reverse_iterator<T>
	operator+(const typename ft::reverse_iterator<T>::difference_type &n,
				const ft::reverse_iterator<T> it)
	{
		return (it + n);
	}

	template<typename T_L, typename T_R>
	typename ft::reverse_iterator<T_L>::difference_type
	operator-(const ft::reverse_iterator<T_L> lit,
			  const ft::reverse_iterator<T_R> rit)
	{
		return (rit.base() - lit.base());
	}

} // namespace ft

#endif
