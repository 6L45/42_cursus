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
			typedef	T												value_type;
			typedef	Alloc											allocator_type;
			typedef	typename allocator_type::const_reference		const_reference;
			typedef	typename allocator_type::pointer				pointer;
			typedef typename allocator_type::size_type				size_type;
			typedef typename ft::random_access_iterator<value_type>	iterator;

		// CONSTRUCT DESTRUCT
			Vector(const allocator_type &alloc = allocator_type());
			~Vector();

			iterator	begin(void);
			iterator	end(void);
//			iterator	rbegin();
//			iterator	rend();
//
//			assign();
			
		// ELEMENT ACCESS
			value_type	at(unsigned int n);
			value_type	&front(void);
			value_type	&back(void);
			value_type	operator[](unsigned int n)
				{ return this->at(n); }
		// ---------------------------------------------------

		
		// CAPACITY
			bool		empty(void);
			size_type	size(void);
//			size_type	max_size(void); FIRST ==> finish iterator
			void		reserve(size_t n);
			size_type	capacity(void);
//			void		shrink_to_fit(void); CHECK si a faire ou non
		// ---------------------------------------------------

		// MODIFIERS
			void	clear();
//			insert();	FIRST ==> finish iterator
//			emplace();	CHECK si a faire ou non
//			erase();
			void		push_back(value_type val);
//			emplace_back();
//			pop_back();
//			resize();
			void	swap(ft::Vector<value_type> &other);
//		--------------------------------------------------------
//
//			operator=();
//			operator==();
//			operator!=();
//			operator<();
//			operator<=();
//			operator>();
//			operator>=();
//			operator<=>();
//			std::swap();
//			erase();
//			erase_if();
			
		private :
			allocator_type	_alloc;
			pointer		_start;
			pointer		_end;
			pointer		_end_capacity;
	};
}

#include "vector.ipp"

#endif

