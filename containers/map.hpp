#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iostream>
# include <iterator>
# include <stdlib.h>
# include <utility>
# include <functional>

# include "enable_if.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
//# include "binary_search_tree.hpp"

enum COLOR
{
	RED,
	BLACK
};

namespace ft
{
	template <class T1, class T2>
	struct pair
	{
		typedef T1		first_arg;
		typedef T2		second_arg;

		first_arg	first;
		second_arg	second;

		pair() {}

		template <class U, class V>
		pair(const pair<U, V> &cpy)
		{
			this->first = cpy.first;
			this->second = cpy.second;
		}

		pair(const T1 &one, const T2 &two)
		{
			this->first = one;
			this->second = two;
		}

		pair &operator=(const pair &cmp)
		{
			if (*this == cmp)
				return (*this);

			this->first = cmp.first;
			this->second = cmp.second;

			return (*this);
		}
	}; //struct pair


	template<class T1, class T2>
	bool	operator==(const ft::pair<T1, T2> &cmped, const ft::pair<T1, T2> &cmping)
		{ return (cmped.first == cmping.first && cmped.second == cmped.second); }

	template<class Key, class T, class Compare = std::less<Key>,
			class Alloc = std::allocator<std::pair<const Key, T> > >

	class map
	{
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

/*			typedef typename ft::random_access_iterator<value_type>			iterator;
			typedef typename ft::random_access_iterator<const value_type>	const_iterator;
			typedef typename ft::reverse_iterator<value_type>				reverse_iterator;
			typedef typename ft::reverse_iterator<const value_type>			const_reverse_iterator;

			typedef typename ft::Binary_search_tree<value_type, key_compare>::iterator iterator;
			typedef typename ft::Binary_search_tree<value_type, key_compare>::const_iterator const_iterator;
			typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
			typedef size_t size_type;
*/

		// CONSTRUCT DESTRUCT
/*			template<class inputIt>
			map(inputIt first, inputIt last,
				const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<inputIt>::value, inputIt>::type * = NULL);
*/			map(const key_compare &comp = key_compare(),
									const allocator_type &alloc = allocator_type());
/*			map(const ft::map<Key, T> &cp);

			map operator=(const ft::map<Key, T> &cpy);

*/			virtual ~map() {};
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
			iterator*/void			insert(value_type val);
/*			iterator*/void			erase(value_type val);
/*			void				swap();

		//LOOKUP
			size_type			count();
			iterator Node			*find(value_type val); */
/*			std::pair<iterator, iterator>	equal_range();
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

			class value_compare
			{
				friend class map<key_type, mapped_type, key_compare, Alloc>;
				protected:
					Compare						comp;
					value_compare(Compare c)
						{ this->comp = c; }

				public:
					bool operator()(const value_type &x, const value_type &y) const
						{ return (comp(x.first, y.first)); }
			};

			class Node
			{
				typedef	typename ft::map<Key, T, Compare, Alloc>::Node	node;

				public:
					value_type		val;
					node			*left;
					node			*right;
					node			*parent;
					COLOR			color;

					// CONSTRUCT
					Node(value_type &val);
					
					node	*uncle();
					node	*sibling();	
					void	move_down(Node *nParent);

					bool has_red_child();
					bool is_on_left();

			}; // class Node
			
			Node			*_root;
			allocator_type	_alloc;
			size_t			_size;

			void	left_rotate(Node *x);
			void	right_rotate(Node *x);
			void	swap_colors(Node *x1, Node *x2);
			void	swap_values(Node *u, Node *v);
			void	fix_red_red(Node *x);
			Node	*successor(Node *x);
			Node	*BSTreplace(Node *x);
			void	delete_node(Node *v);
			void	fix_double_black(Node *x);
//			void	level_order(Node *x);
//			void	in_order(Node *x);

			

		public :
			Node			*find(value_type val); // TO MOVE UP (return value Node to swap with iterator)

	}; // class map

//# include "map_overloads.ipp"

# include "node.ipp"
# include "bst_methods.ipp"
# include "map.ipp"

} // namespace ft


#endif
