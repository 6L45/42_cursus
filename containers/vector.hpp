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
			typedef	T												value_type;
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

		// CONSTRUCT DESTRUCT
			vector(const allocator_type &alloc = allocator_type());
			vector(std::initializer_list<value_type> lst);
			vector(const ft::vector<value_type> &cp);
			vector(size_t count);

			virtual	~vector();

		// ITERATOR
			iterator	begin(void) const;
			iterator	end(void) const;
//			iterator	rbegin();
//			iterator	rend();
//
			void	assign(size_t count, const value_type &val);

			template<class inputIt>
			void	assign(inputIt first, inputIt last,
					typename std::enable_if<!std::is_integral<inputIt>::value,
								inputIt>::type* = nullptr);

		// ELEMENT ACCESS
			value_type	at(unsigned int n);
			value_type	&front(void);
			value_type	&back(void);
		// ---------------------------------------------------

		
		// CAPACITY
			bool		empty(void);
			size_type	size(void) const;
//			size_type	max_size(void); FIRST ==> finish iterator
			void		reserve(size_t n);
			size_type	capacity(void) const;
//			void		shrink_to_fit(void); CHECK si a faire ou non
		// ---------------------------------------------------

		// MODIFIERS
			void		clear();
//			insert();	FIRST ==> finish iterator
//			emplace();	CHECK si a faire ou non
//			erase();
			void		push_back(value_type val);
//			emplace_back();
//			pop_back();
//			resize();
			void		swap(ft::vector<value_type> &other);
//		--------------------------------------------------------

		// OVERLOADS
			value_type	&operator[](size_t n)
			{
				return (*(this->_start + n));
			}
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

