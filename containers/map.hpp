#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iostream>
# include <iterator>
# include <stdlib.h>
# include <utility>
# include <functional>
# include <iterator>
# include <vector>

# include "vector.hpp"
# include "enable_if.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"

enum COLOR
{
	BLACK,
	RED
};

namespace ft
{

	template <class T1, class T2>
	struct pair
	{
		public:
			typedef T1 first_type;

			typedef T2 second_type;

			first_type first;
			second_type second;

			pair()
				: first(),
				second()
			{
			}

			template <class U, class V>
			explicit pair(const pair<U, V> &pr)
				: first(pr.first),
				second(pr.second)
			{
			}

			pair(const first_type &a, const second_type &b)
				: first(a),
				second(b)
			{
			}

			pair &operator=(const pair &pr)
			{
				if (*this == pr)
					return (*this);
				this->first = pr.first;
				this->second = pr.second;
				return (*this);
			}
	};

	template <class T1, class T2>
	bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{
		return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{
		return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));
	}

	template <class T1, class T2>
	bool operator<=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{
		return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	ft::pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (ft::pair<T1, T2>(x, y));
	}

	class bidirectional_iterator_tag {};

	template <class Key, class T, class Node,
				class Alloc = std::allocator<ft::pair<const Key, T>>>
	class BST_iterator
	{
		public:
			typedef Node										node;
			typedef ft::pair<const Key, T>						value_type;

			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::size_type			size_type;

			typedef	node*										nodePointer;
			typedef node&										nodeRef;

			typedef ft::bidirectional_iterator_tag	iterator_category;

			BST_iterator(nodePointer node)
			{
				if (node == NULL)
					this->_node = NULL;
				else
					this->_node = node;
			}
			BST_iterator(const BST_iterator& bst_it)
			{
				if (*this == bst_it)
					return;

				this->_node = bst_it._node;
			}
			
			BST_iterator &operator=(const BST_iterator	&bst_it)
			{
				if (*this == bst_it)
					return (*this);

				this->_node = bst_it._node;

				return (*this);
			}			

			virtual ~BST_iterator() { }	

			bool operator==(const BST_iterator &cmped)
			{
				if (cmped._node == NULL && this->_node == NULL)
					return (true);
				else if (cmped._node->endpoint && this->_node->endpoint)
					return (true);				
				else if (cmped._node == NULL || this->_node == NULL)
					return (false);
				else if (cmped._node->endpoint || this->_node->endpoint)
					return (false);

				return (this->_node->val == cmped._node->val);
			}

			reference operator*() const
				{ return (*this->_node->val); }
			
			pointer operator->() const
				{ return  (this->_node->val); }

			friend bool operator!=(const BST_iterator& cmped, const BST_iterator& cmping)
				{ return (cmped._node != cmping._node); }

			friend bool operator>=(const BST_iterator& cmped, const BST_iterator& cmping)
				{ return (cmped._node >= cmping._node); }

			friend bool operator<=(const BST_iterator& cmped, const BST_iterator& cmping)
				{ return (cmped._node <= cmping._node); }

			friend bool operator==(const BST_iterator& cmped, const BST_iterator& cmping)
				{ return (cmped._node == cmping._node); }

			BST_iterator	&operator++(void)
			{
				this->_node = this->_node->successor(this->_node);
				return (*this);
			}

			BST_iterator	&operator--(void)
			{
				this->_node = this->_node->predecessor(this->_node);
				return (*this);
			}

			BST_iterator	operator++(int)
			{
				BST_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			BST_iterator	operator--(int)
			{
				BST_iterator tmp(*this);
				operator--();
				return (tmp);
			}

			BST_iterator	&operator-(const int n)
			{
				if (n > 0)
				{
					for (int turns = n; turns; turns--)
						this->_node = this->_node->predecessor(this->_node);
				}
				else
				{
					for (int turns = n; turns; turns++)
						this->_node = this->_node->successor(this->_node);
				}
				
				return (*this);
			}
			
			BST_iterator	&operator+(const int n)
			{
				if (n > 0)
				{
					for (int i = 0; i < n; i++)
						this->_node = this->_node->successor(this->_node);
				}
				else
				{
					for (int i = 0; i < n; i--)
						this->_node = this->_node->predecessor(this->_node);
				}

				return (*this);
			}
		
		private:
			nodePointer	_node;
	};

	template <class Key, class T, class Compare = std::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T>>>
	class map
	{
		class	Node;

		public :
			typedef T 											mapped_type;
			typedef Key											key_type;
			typedef ft::pair<const Key, T>						value_type;
			typedef Compare										key_compare;
			typedef Alloc										allocator_type;
			typedef typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef typename allocator_type::size_type			size_type;

			typedef typename ft::BST_iterator<key_type, mapped_type, Node, Alloc>
																iterator;
			typedef typename ft::BST_iterator<key_type, mapped_type, Node, Alloc>
																const_iterator;
//			typedef typename ft::BST_iterator<key_type, mapped_type, Node, Alloc>::difference_type
//																difference_type;

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

		// CONSTRUCT DESTRUCT
			template<class inputIt>
			map(inputIt first, inputIt last,
				const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<inputIt>::value, inputIt>::type * = NULL);
			map(const key_compare &comp = key_compare(),
					const allocator_type &alloc = allocator_type());
			map(const ft::map<Key, T> &cp);

			virtual ~map();
			map &operator=(const ft::map<Key, T> &cpy);


		//ELEMENT ACCESS
			mapped_type						&at(const key_type &key);
			mapped_type						&operator[](const key_type &key);

		//CAPACITY
			bool							empty() const;
			size_type						size() const;
			size_type						max_size() const;

		//MODIFIERS
			void							clear(void);
			template <class InputIterator>
			void							insert (InputIterator first, InputIterator last,
													typename ft::enable_if<!ft::is_integral
													<InputIterator>::value, InputIterator>::type * = NULL);

			ft::pair<iterator, bool>		insert(const value_type &val);
			iterator						insert(iterator pos, const value_type &val);
			void							erase(iterator pos);
			void							erase(iterator first, iterator last);
			size_t							erase(const	key_type &k);
			void							swap(map &x);

		//LOOKUP
			size_type						count(const key_type &key) const;
			iterator						find(const key_type &key);
			const_iterator					find (const key_type& k) const;
			iterator						lower_bound(const key_type &key);
			const_iterator					lower_bound (const key_type& k) const;
			iterator						upper_bound(const key_type &key);
			const_iterator					upper_bound (const key_type& k) const;
			ft::pair<iterator, iterator>				equal_range(const key_type &key);
			ft::pair<const_iterator, const_iterator>	equal_range (const key_type& k) const;

		//OBSERVERS
			key_compare	key_comp() const
				{ return ( key_compare()); }

			value_compare	value_comp() const
				{ return ( value_compare(key_compare())); }

		//ITERATORS
			iterator						begin(void);
			const_iterator					begin() const;
			iterator						end(void);
			const_iterator					end() const;

/*			reverse_iterator rbegin();
			const_reverse_iterator rbegin() const;
			reverse_iterator rend();
			const_reverse_iterator rend() const;
*/
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
					bool			endpoint = false;

					bool	is_left()
					{
						if (this->parent == NULL
							|| this == this->parent->right)
							return (false);
						return (true);
					}

					bool	is_right()
					{
						if (this->parent == NULL
							|| this == this->parent->left)
							return (false);
						return (true);
					}

					bool	is_root()
					{
						if (this->parent == NULL)
							return (true);
						return (false);
					}

					node	*sibling()
					{
						if (this->parent)
						{
							if (this->is_left())
								return (this->parent->right);
							else
								return (this->parent->left);
						}
						return (NULL);
					}

					Node	*successor(node *x)
					{
						if (x->right != NULL)
						{
							x = x->right;
							while (x->left)
								x = x->left;
							
							return (x);
						}

						Node	*y = x->parent;
						while (y != NULL && x == y->right)
						{
							x = y;
							y = y->parent;
						}
						return (y);
					}

					Node	*predecessor(node *x)
					{
						if (x->left != NULL)
						{
							x = x->left;
							while (x->right)
								x = x->right;

							return (x);
						}

						Node	*y = x->parent;
						while (y != NULL && x == y->left)
						{
							x = y;
							y = y->parent;
						}

						return (y);
					}

			}; // class Node

			allocator_type			_alloc;
			Compare					_comp;
			Node					*_root;
			Node					*_endPoint;
			size_t					_nodesNbr;

			void	insertFix(Node *node);
			void	leftRotate(Node *node);
			void	rightRotate(Node *node);
			void	rbTransplant(Node *u, Node *v);
			Node	*minimum(Node *node);
			Node	*maximum(Node *node);
			void	deleteFix(Node *node);
			Node	*searchTreeHelper(Node *node, const key_type &val) const;
			void 	deleteNodeHelper(Node *node, const key_type key);
			void	fixDoubleBlack(Node *x);
			void	clearHelper(Node *x);
			void	endPointUpdate(void);
	
	}; // class map
} // namespace ft

# include "map.ipp"

#endif

/*
if (this->_node->is_right())
{
	if (this->_node->right == NULL)
	{
		nodePointer	tmp;
		tmp = this->_node;

		while (tmp->is_right())
			tmp = tmp->parent;

		if (tmp->is_root())
			move_to_the_right();
		else
			this->_node = tmp->parent;
	}
	else
		move_to_the_right();
}
else if (this->_node->is_left())
{
	if (this->_node->right == NULL)
		this->_node = this->_node->parent;
	else
		move_to_the_right();
}
else
	move_to_the_right();

return (*this);

*/	