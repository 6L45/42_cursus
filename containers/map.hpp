#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iostream>
# include <iterator>
# include <stdlib.h>
# include <utility>

# include "enable_if.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"

namespace ft
{

	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<std::pair<const Key, T>> >
	class map
	{
		class value_compare
		{
			friend class map<key_type, mapped_type, key_compare, Alloc>;

			protected:
				Compare comp;
				value_compare(Compare c) : comp(c) {}

			public:
				bool operator()(const value_type &x, const value_type &y) const
					{ return (comp(x.first, y.first)); }
		};

		 public :
			typedef T 														mapped_type;
			typedef Key														key_type;
			typedef std::pair<const Key, T>									value_type;
			typedef Compare													key_compare;
			typedef Alloc 													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::size_type						size_type;
			typedef typename ft::random_access_iterator<value_type>			iterator;
			typedef typename ft::random_access_iterator<const value_type>	const_iterator;
			typedef typename ft::reverse_iterator<value_type>				reverse_iterator;
			typedef typename ft::reverse_iterator<const value_type>			const_reverse_iterator;
/*
			typedef typename ft::Binary_search_tree<value_type, key_compare>::iterator iterator;
			typedef typename ft::Binary_search_tree<value_type, key_compare>::const_iterator const_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;
*/

			// CONSTRUCT DESTRUCT
			template<class inputIt>
			map(inputIt first, inputIt last,
				const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<inputIt>::value, inputIt>::type * = NULL);
			map(const key_compare &comp = key_compare(),
									const allocator_type &alloc = allocator_type());
			map(const ft::map<Key, T> &cp);

			map operator=(const ft::map<Key, T> &cpy);

			virtual ~map();
		/*
			//ELEMENT ACCESS
				reference			at();
				const_reference		operator[]();

			//CAPACITY
				bool				empty();
				size_type			size();
				size_type			max_size();

			//MODIFIERS
				void				clear();
				iterator			insert();
				iterator			erase();
				void				swap();


			//LOOKUP
				size_type			count();
				iterator			find();
				std::pair<iterator, iterator>	equal_range();
				iterator			lower_bound();
				iterator			upper_bound();

			//OBSERVERS
				key_comp();
				value_comp();

			//ITERATORS
				iterator			begin();
				iterator			end();
		*/
		private :
			allocator_type									_alloc;
			Compare											_comp;
			binary_search_tree<value_type, key_compare>		_binary_srch;

	}; // class map

//# include "map_overloads.ipp"

} // namespace ft

# include "map.ipp"

#endif
