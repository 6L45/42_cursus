#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iostream>
# include <iterator>
# include <stdlib.h>
# include <utility>
# include <functional>
# include <iterator>

# include "enable_if.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
//# include "binary_search_tree.hpp"

enum COLOR
{
	BLACK,
	RED
};

namespace ft
{
	class bidirectional_iterator_tag {};

	template <typename T, class Compare, class Distance = __PTRDIFF_TYPE__>
	class BST_iterator
	{
		public:
			typedef T								value_type;
			typedef Distance						difference_type;
			typedef value_type*						pointer;
			typedef value_type&						reference;
			typedef ft::bidirectional_iterator_tag	iterator_category;
	
			BST_iterator(pointer node, const Compare &comp = Compare())
			{
				this->_node = node;
				this->_comp = comp;
			}

			virtual ~BST_iterator() { }	

			bool operator==(const BST_iterator &cmped)
				{ return (this->_node == cmped._node); }

			reference operator*() const
				{ return (this->_node->val); }
			
			pointer operator->() const
				{ return  (&this->_node->val); }
			
			pointer	get_node()
				{ return (this->_node); }
		private:
			pointer	_node;
			Compare	_comp;
	};

	template <class Key, class T, class Compare = std::less<Key>,
				class Alloc = std::allocator<std::pair<const Key, T>>>
	class map
	{
		class	Node;

		public :
			typedef T 																mapped_type;
			typedef Key																key_type;
			typedef std::pair<const Key, T>											value_type;
			typedef Compare															key_compare;
			typedef Alloc 															allocator_type;
			typedef typename allocator_type::reference								reference;
			typedef typename allocator_type::const_reference						const_reference;
			typedef typename allocator_type::pointer								pointer;
			typedef typename allocator_type::const_pointer							const_pointer;
			typedef typename allocator_type::size_type								size_type;

			typedef typename ft::BST_iterator<Node, key_compare>					iterator;
/*			typedef typename ft::BST_const_iterator<Node>							const_iterator;
			typedef typename ft::BST_iterator<Node, key_compare>::difference_type	difference_type;
*/

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map;

				public:
					bool	operator() (const value_type& lhs, const value_type& rhs) const
						{ return (comp(lhs.first, rhs.first)); }
					bool	operator() (const key_type& k, const value_type& rhs) const
						{ return (comp(k, rhs.first)); }
					bool	operator() (const value_type& lhs, const key_type& k) const
						{ return (comp(lhs.first, k)); }

				protected:
					key_compare					comp;

					value_compare(Compare c)
						{ this->comp = c; }
			};


//			TODO()
			//	REMAINING FUNCTION
			//	OPERATOR OVERLOADS

		// CONSTRUCT DESTRUCT
			template<class inputIt>
			map(inputIt first, inputIt last,
				const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<inputIt>::value, inputIt>::type * = NULL);
			map(const key_compare &comp = key_compare(),
					const allocator_type &alloc = allocator_type());
			map(const ft::map<Key, T> &cp);

			virtual ~map() {};
			map &operator=(const ft::map<Key, T> &cpy);


		//ELEMENT ACCESS
			mapped_type			&at(const key_type &key);
			mapped_type			&operator[](const key_type &key);

		//CAPACITY
			bool							empty();
			size_type						size();
			size_type						max_size();

		//MODIFIERS
			void							clear(void);
			template <class InputIterator>
			void							insert (InputIterator first, InputIterator last,
							typename ft::enable_if<!ft::is_integral
							<InputIterator>::value, InputIterator>::type *);

			std::pair<iterator, bool>		insert(const value_type &val);
			iterator						insert(iterator pos, const value_type &val);
			void							erase(iterator pos);
			void							erase(iterator first, iterator last);
			size_t							erase(const	key_type &k);
			void							swap(map &x);

		//LOOKUP
			size_type						count(const key_type &key) const;
			iterator						find(const key_type &key) const;
/*			std::pair<iterator, iterator>	equal_range();
			iterator						lower_bound();
			iterator						upper_bound();

*/		//OBSERVERS
			key_compare	key_comp() const
				{ return ( key_compare()); }

			value_compare	value_comp() const
				{ return ( value_compare(key_compare())); }

		//ITERATORS
			iterator						begin(void);
			iterator						end(void) const;

		private:
			class Node
			{
				typedef	typename ft::map<Key, T, Compare, Alloc>::Node	node;

				public:
					pointer			val;
					node			*left;
					node			*right;
					node			*parent;
					COLOR			color;

			}; // class Node

			allocator_type			_alloc;
			Compare					_comp;
			Node					*_root;
			Node					*TNULL;
			size_t					_nodesNbr;

			void	insertFix(Node *node);
			void	leftRotate(Node *node);
			void	rightRotate(Node *node);
			void	rbTransplant(Node *u, Node *v);
			Node	*minimum(Node *node);
			void	deleteFix(Node *node);
			Node	*searchTreeHelper(Node *node, const key_type &val) const;

	}; // class map
} // namespace ft

# include "map.ipp"

#endif
