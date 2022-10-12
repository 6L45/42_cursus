#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <memory>
# include <iostream>
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
# include "bidirectional_iterator.hpp"
# include <iterator>
# include <type_traits>
# include <stdlib.h>

# define out	std::cout <<
# define nl	std::endl

namespace ft
{
	template <bool Cond, class T = void>
	struct enable_if {};
	template <class T>
	struct enable_if<true, T>
		{ typedef T type; };
	template <bool is_integral, typename T>
	struct is_integral_res
	{
		typedef T type;
		static const bool value = is_integral;
	};

	template <typename>
	struct is_integral_type : public is_integral_res<false, bool> {};
	template <>
	struct is_integral_type<bool> : public is_integral_res<true, bool> {};
	template <>
	struct is_integral_type<char> : public is_integral_res<true, char> {};
	template <>
	struct is_integral_type<signed char> : public is_integral_res<true, signed char> {};
	template <>
	struct is_integral_type<short int> : public is_integral_res<true, short int> {};
	template <>
	struct is_integral_type<int> : public is_integral_res<true, int> {};
	template <>
	struct is_integral_type<long int> : public is_integral_res<true, long int> {};
	template <>
	struct is_integral_type<long long int> : public is_integral_res<true, long long int> {};
	template <>
	struct is_integral_type<unsigned char> : public is_integral_res<true, unsigned char> {};
	template <>
	struct is_integral_type<unsigned short int> : public is_integral_res<true, unsigned short int> {};
	template <>
	struct is_integral_type<unsigned int> : public is_integral_res<true, unsigned int> {};
	template <>
	struct is_integral_type<unsigned long int> : public is_integral_res<true, unsigned long int> {};
	template <>
	struct is_integral_type<unsigned long long int> : public is_integral_res<true, unsigned long long int> {};

	template <typename T>
	struct is_integral : public is_integral_type<T> {};

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
					typename ft::enable_if<!ft::is_integral<inputIt>::value,
											inputIt>::type * = nullptr);
			vector(const allocator_type &alloc = allocator_type());
			vector(std::initializer_list<value_type> lst);
			vector(const ft::vector<value_type> &cp);
			vector(const size_t count, value_type val = value_type(),
					const allocator_type &alloc = allocator_type());
			vector	&operator=(const ft::vector<value_type, allocator_type> &cpy);

			virtual	~vector();

		// ITERATORS
			iterator begin(void);
			iterator end(void);
			const_iterator begin(void) const;
			const_iterator end(void) const;

			reverse_iterator rbegin(void);
			reverse_iterator rend(void);
			const_reverse_iterator rend(void) const;
			const_reverse_iterator rbegin(void) const;

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
										typename ft::enable_if<!ft::is_integral<inputIt>::value,
																inputIt>::type * = nullptr);
			void				assign(size_t count, const value_type &val);
			void				clear();
			iterator			insert(iterator pos, const value_type &val);
			iterator			insert(iterator pos, size_t n, const value_type &val);
			template<class inputIt>
			void				insert(iterator pos, inputIt first, inputIt last,
									typename ft::enable_if<!ft::is_integral<inputIt>::value,
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
