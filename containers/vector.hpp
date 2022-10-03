#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include "random_access_iterator.hpp"
# include <iterator>
# include <type_traits>
# include <stdlib.h>

# define out	std::cout <<
# define nl	std::endl

namespace ft
{

	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
		public :
			typedef	T
				value_type;
			typedef	Alloc
				allocator_type;
			typedef	typename allocator_type::const_reference
				const_reference;
			typedef	typename allocator_type::pointer
				pointer;
			typedef typename allocator_type::size_type
				size_type;
			typedef typename ft::random_access_iterator<value_type>
				iterator;
			typedef ft::random_access_iterator<const value_type>
				const_iterator;	

		// CONSTRUCT DESTRUCT
			template<class inputIt>
			vector(inputIt first, inputIt last,
					typename std::enable_if<!std::is_integral<inputIt>::value,
											inputIt>::type * = nullptr);
			vector(const allocator_type &alloc = allocator_type());
			vector(std::initializer_list<value_type> lst);
			vector(const ft::vector<value_type> &cp);
			vector(size_t count);
			vector	&operator=(const ft::vector<value_type, allocator_type> &cpy);

			virtual	~vector();

		// ITERATORS
			iterator	begin(void) const;
			iterator	end(void) const;
//			iterator	rbegin();
//			iterator	rend();

		// ELEMENT ACCESS
			value_type	&at(const unsigned int n) const;
			value_type	&front(void) const;
			value_type	&back(void) const;
		
		// CAPACITY
			bool		empty(void) const;
			size_type	size(void) const;
			size_type	max_size(void) const;
			void		reserve(size_t n);
			size_type	capacity(void) const;

		// MODIFIERS
			template<class inputIt>
			void		assign(inputIt first, inputIt last,
								typename std::enable_if<!std::is_integral<inputIt>::value,
														inputIt>::type* = nullptr);
			void		assign(size_t count, const value_type &val);
			void		clear();
			iterator	insert(iterator pos, size_t n, const value_type &val);
//			erase();
			void		push_back(value_type val);
//			pop_back();
//			resize();
			void		swap(ft::vector<value_type> &other);

		// OVERLOADS
			value_type	&operator[](size_t n)
			{
				return (*(this->_start + n));
			}
			bool	operator==(const ft::vector<value_type> &cmp) const;
			bool	operator!=(const ft::vector<value_type> &cmp) const;
			bool	operator<(const ft::vector<value_type> &cmp) const;
			bool	operator<=(const ft::vector<value_type> &cmp) const;
			bool	operator>(const ft::vector<value_type> &cmp) const;
			bool	operator>=(const ft::vector<value_type> &cmp) const;
			
		private :
			allocator_type	_alloc;
			pointer		_start;
			pointer		_end;
			pointer		_end_capacity;
	};
}

#include "vector.ipp"

#endif

