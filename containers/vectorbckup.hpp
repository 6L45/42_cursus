#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
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
			typedef	T														value_type;
			typedef	Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef	typename allocator_type::const_reference				const_reference;
			typedef	typename allocator_type::pointer						pointer;
			typedef typename allocator_type::size_type						size_type;
			typedef typename ft::random_access_iterator<value_type>			iterator;
			typedef typename ft::random_access_iterator<const value_type>	const_iterator;	
			typedef	typename ft::reverse_iterator<value_type>				reverse_iterator;
			typedef typename ft::reverse_iterator<const value_type>			const_reverse_iterator;

		// CONSTRUCT DESTRUCT
			template<class inputIt>
			vector(inputIt first, inputIt last,
					typename std::enable_if<!std::is_integral<inputIt>::value,
											inputIt>::type * = nullptr);
			vector(const allocator_type &alloc = allocator_type());
			vector(std::initializer_list<value_type> lst);
			vector(const ft::vector<value_type> &cp);
			vector(const size_t count);
			vector(const size_t count, value_type val);
			vector	&operator=(const ft::vector<value_type, allocator_type> &cpy);

			virtual	~vector();

		// ITERATORS
			iterator begin(void) {
				return (this->_start);
			}
			const_iterator begin(void) const {
				return (this->_start);
			}
			reverse_iterator rbegin(void) {
				return (this->_end);
			}
			const_reverse_iterator rbegin(void) const {
				return (this->_end);
			}
			iterator end(void) {
				return (this->_end);
			}
			const_iterator end(void) const {
				return (this->_end);
			}
			reverse_iterator rend(void) {
				return (this->_start);
			}
			const_reverse_iterator rend(void) const {
				return (this->_start);
			}

		// ELEMENT ACCESS
			reference			at(const unsigned int n);
			reference			front(void);
			reference			back(void);
			reference			operator[](const size_t n);

			const_reference		at(const unsigned int n) const;
			const_reference		front(void) const;
			const_reference		back(void) const;
			const_reference		operator[](const size_t n) const;

		// CAPACITY
			bool				empty(void) const;
			size_type			size(void) const;
			size_type			max_size(void) const;
			void				reserve(size_t n);
			size_type			capacity(void) const;

		// MODIFIERS
			template<class inputIt>
			void				assign(inputIt first, inputIt last,
										typename std::enable_if<!std::is_integral<inputIt>::value,
																inputIt>::type* = nullptr);
			void				assign(size_t count, const value_type &val);
			void				clear();
			iterator			insert(iterator pos, const value_type &val);
			iterator			insert(iterator pos, size_t n, const value_type &val);
			template<class inputIt>
			void				insert(iterator pos, inputIt first, inputIt last,
									typename std::enable_if<!std::is_integral<inputIt>::value,
															inputIt>::type * = nullptr);
			iterator			erase(iterator pos);
			iterator			erase(iterator first, iterator last);
			void				push_back(value_type val);
			void				pop_back();
			void				resize(size_t n, value_type val = value_type());
			void				swap(ft::vector<value_type> &other);

		private :
			allocator_type	_alloc;
			pointer		_start;
			pointer		_end;
			pointer		_end_capacity;
	};

// NON - MEMBER FUNCTIONS OVERLOADS

# include "vector_overloads.ipp"
/*
	template<class T, class Allocator>
	bool	operator!=(const ft::vector<T, Allocator> &vec, const ft::vector<T, Allocator> &cmp);

	template <class T, class Allocator>
	bool	operator<(const ft::vector<T, Allocator> &vec, const ft::vector<T, Allocator> &cmp);

	template<class T, class Allocator>
	bool	operator<=(const ft::vector<T, Allocator> &vec, const ft::vector<T, Allocator> &cmp);

	template<class T, class Allocator>
	bool	operator>(const ft::vector<T, Allocator> &vec, const ft::vector<T, Allocator> &cmp);

	template<class T, class Allocator>
	bool	operator>=(const ft::vector<T, Allocator> &vec, const ft::vector<T, Allocator> &cmp);
*/

} // namespace ft

# include "vector.ipp"

#endif

