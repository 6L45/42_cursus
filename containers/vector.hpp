#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstddef>

# include "utils.hpp"
# include "enable_if.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
		public :
			typedef	T											value_type;
			typedef	Alloc										allocator_type;
			typedef ptrdiff_t									difference_type;
			typedef typename allocator_type::reference			reference;
			typedef	typename allocator_type::const_reference	const_reference;
			typedef	typename allocator_type::pointer			pointer;
			typedef typename allocator_type::size_type			size_type;

			class iterator : public random_access_iterator<value_type>
			{
				public:
					typedef random_access_iterator<value_type>	super;
					typedef value_type							&reference;
					typedef value_type							*pointer;
					
					iterator(value_type *src) : random_access_iterator<value_type>(src) {}
					iterator(void): random_access_iterator<value_type>() {};
					iterator(const iterator &src): random_access_iterator<value_type>(src) {};

					reference			operator*(void) const
						{ return (super::operator*()); }
					pointer				operator->(void) const
						{ return (super::operator->()); }
					iterator			&operator+=(difference_type n)
					{
						super::operator+=(n);
						return (*this);
					}
					iterator			&operator-=(difference_type n)
					{
						super::operator-=(n);
						return (*this);
					}
					reference			operator[](difference_type n) const
						{ return (super::operator[](n)); }
					difference_type		operator-(const random_access_iterator<value_type> &n) const
						{ return super::operator-(n); }
					iterator			operator-(difference_type n) const
						{ return super::operator-(n); }
					iterator			operator+(difference_type n) const
						{ return super::operator+(n); }
					friend iterator		operator+(difference_type n, const iterator &rhs)
						{ return rhs.operator+(n); }
					iterator &operator++(void)
					{
						super::operator++();
						return *this;
					}
					iterator operator++(int)
						{ return super::operator++(0); }
					iterator &operator--(void)
					{
						super::operator--();
						return *this;
					}
					iterator operator--(int)
						{ return super::operator--(0); }

				// make the copy constructor usable within the class
				// but not outside the class making then the construction by iterator by default on const_iterator
				private:
					iterator(const random_access_iterator<value_type> &src): random_access_iterator<value_type>(src) {}
			};

			class const_iterator : public random_access_iterator<value_type>
			{
				public:
					typedef random_access_iterator<value_type>		super;
					typedef const value_type 						&reference;
					typedef const value_type 						*pointer;

					const_iterator(value_type *src): random_access_iterator<value_type>(src) {}
					const_iterator(void): random_access_iterator<value_type>() {}
					const_iterator(const random_access_iterator<value_type> &src): random_access_iterator<value_type>(src){}

					reference operator*(void) const
						{ return (super::operator*()); }
					pointer operator->(void) const
						{ return (super::operator->()); }
					const_iterator &operator+=(difference_type n)
					{
						super::operator+=(n);
						return (*this);
					}
					const_iterator &operator-=(difference_type n)
					{
						super::operator-=(n);
						return (*this);
					}
					reference operator[](difference_type n) const
						{ return (operator[](n)); }

					difference_type operator-(const random_access_iterator<value_type> &n) const
						{ return super::operator-(n); }
					const_iterator operator-(difference_type n) const
						{ return super::operator-(n); }
					const_iterator operator+(difference_type n) const
						{ return super::operator+(n); }
					friend const_iterator operator+(difference_type n, const const_iterator &rhs)
						{ return rhs.operator+(n); }
					const_iterator &operator++(void)
					{
						super::operator++();
						return (*this);
					}
					const_iterator operator++(int)
						{ return super::operator++(0); }
					const_iterator &operator--(void)
					{
						super::operator--();
						return *this;
					}
					const_iterator operator--(int)
						{ return super::operator--(0); }
			};
			typedef	typename ft::reverse_iterator<iterator>			reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		// CONSTRUCT DESTRUCT
			template<class inputIt>
			vector(inputIt first, inputIt last,
					typename ft::enable_if<!ft::is_integral<inputIt>::value,
											inputIt>::type * = NULL);
			vector(const allocator_type &alloc = allocator_type());
//			vector(std::initializer_list<value_type> lst); <--- not c++98
			vector(const ft::vector<value_type> &cp);
			vector(const size_t count, value_type val = value_type(),
					const allocator_type &alloc = allocator_type());
			vector	&operator=(const ft::vector<value_type, allocator_type> &cpy);

			virtual	~vector();

		// ELEMENT ACCESS
			reference				at(const unsigned int n);
			reference				front(void);
			reference				back(void);
			reference				operator[](const size_t n);

			const_reference			at(const unsigned int n) const;
			const_reference			front(void) const;
			const_reference			back(void) const;
			const_reference			operator[](const size_t n) const;

		// CAPACITY
			bool					empty(void) const;
			size_type				size(void) const;
			size_type				max_size(void) const;
			void					reserve(size_t n);
			size_type				capacity(void) const;

		// MODIFIERS
			template<class inputIt>
			void					assign(inputIt first, inputIt last,
										typename ft::enable_if<!ft::is_integral<inputIt>::value,
																inputIt>::type * = NULL);
			void					assign(size_t count, const value_type &val);
			void					clear();
			iterator				insert(iterator pos, const value_type &val);
			iterator				insert(iterator pos, size_t n, const value_type &val);
			template<class inputIt>
			void					insert(iterator pos, inputIt first, inputIt last,
											typename ft::enable_if<!ft::is_integral<inputIt>::value,
																	inputIt>::type * = NULL);
			iterator				erase(iterator pos);
			iterator				erase(iterator first, iterator last);
			void					push_back(value_type val);
			void					pop_back();
			void					resize(size_t n, value_type val = value_type());
			void					swap(ft::vector<value_type> &other);

		// ITERATORS
			iterator				begin(void);
			iterator				end(void);
			const_iterator			begin(void) const;
			const_iterator			end(void) const;

			reverse_iterator		rbegin(void);
			reverse_iterator		rend(void);
			const_reverse_iterator	rend(void) const;
			const_reverse_iterator	rbegin(void) const;

		private :
			allocator_type			_alloc;
			pointer					_start;
			pointer					_end;
			pointer					_end_capacity;

			template<class inputIt>
			size_t					__itLen(inputIt first, inputIt last);
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
# include "vector_element_access.ipp"
# include "vector_capacity.ipp"
# include "vector_modifiers.ipp"
# include "vector_iterators_ret.ipp"

#endif
