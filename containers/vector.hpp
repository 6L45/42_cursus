#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include "random_access_iterator.hpp"

# define out	std::cout <<
# define nl	std::endl

namespace ft
{

	template<class T, class Alloc = std::allocator<T> >
	class Vector
	{
		public :
			typedef	T						value_type;
			typedef	Alloc						allocator_type;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer		pointer;
			typedef typename allocator_type::size_type		size_type;
			typedef typename ft::random_access_iterator<value_type>	iterator;

			Vector(const allocator_type &alloc = allocator_type());

			void		push_back(value_type val);
			size_type	size(void);
			size_type	max_capacity(void);
			iterator	begin(void);
			iterator	end(void);

		private :
			allocator_type	_alloc;
			pointer		_start;
			pointer		_end;
			pointer		_end_capacity;
	};
}

#include "vector.ipp"

#endif

