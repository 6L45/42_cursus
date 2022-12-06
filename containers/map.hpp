#ifndef MAP_HPP
# define MAP_HPP

# include <memory>
# include <iostream>
# include <iterator>
# include <stdlib.h>
# include <utility>
# include <functional>
# include <iterator>
#include <cstddef>

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

	template <class Ite1, class Ite2>
	bool	equal(Ite1 first1, Ite1 last1, Ite2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return false;
			++first1; ++first2;
		}
		return true;
	}

	template <class Ite1, class Ite2>
	bool	lexicographical_compare(Ite1 first1, Ite1 last1, Ite2 first2, Ite2 last2)
	{
		while (first1 != last1 && first2 != last2 && *first1 == *first2)
		{
			++first1; ++first2;
		}
		if (first1 == last1)
			return (first2 != last2);
		else if (first2 == last2)
			return (false);
		return (*first1 < *first2);
	}
	// -------------------------------------------------------- PAIR
	template <class T1, class T2>
	struct pair
	{
		public:
			T1	first;
			T2	second;

			pair() {}

			template <class U, class V>
			pair(const pair<U, V> &pr): first(pr.first), second(pr.second) {}
			pair(const T1 &a, const T2 &b) :
				first(a), second(b) {}

			pair &operator=(const pair &pr)
			{
				if (*this == pr)
					return (*this);

				this->first = pr.first;
				this->second = pr.second;

				return (*this);
			}

			virtual ~pair() {}
	};

	template <class T1, class T2>
	bool operator==(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{ return (lhs.first == rhs.first && lhs.second == rhs.second); }

	template <class T1, class T2>
	bool operator!=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{ return !(lhs == rhs); }

	template <class T1, class T2>
	bool operator<(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{ return (lhs.first < rhs.first
			|| (!(rhs.first < lhs.first) && lhs.second < rhs.second)); }

	template <class T1, class T2>
	bool operator<=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{ return !(rhs < lhs); }

	template <class T1, class T2>
	bool operator>(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{ return (rhs < lhs); }

	template <class T1, class T2>
	bool operator>=(const ft::pair<T1, T2> &lhs, const ft::pair<T1, T2> &rhs)
		{ return !(lhs < rhs); }

	template <class T1, class T2>
	ft::pair<T1, T2>	make_pair(T1 x, T2 y)
		{ return (ft::pair<T1, T2>(x, y)); }

	// -------------------------------------------------------- PAIR












	// -------------------------------------------------------- ITERATORS
	class bidirectional_iterator_tag {};

	template <class Node, class T, class Distance = __PTRDIFF_TYPE__>
	class BST_iterator
	{
		public:
			typedef T						value_type;
			typedef ptrdiff_t				difference_type;
			typedef value_type&				reference;
			typedef value_type*				pointer;

			typedef ft::bidirectional_iterator_tag				iterator_category;

			BST_iterator()
				{ this->_node = NULL; }

			BST_iterator(Node * node)
				{ this->_node = node; }

			BST_iterator(const BST_iterator& bst_it)
				{ *this = bst_it; }
			
			BST_iterator &operator=(const BST_iterator &bst_it)
			{
				if (this == &bst_it)
					return (*this);

				this->_node = bst_it._node;

				return (*this);
			}			
			
			operator	BST_iterator<Node, const T>(void) const
				{ return BST_iterator<Node, const T>(this->_node); }

			virtual ~BST_iterator() { return; }	


			reference operator*() const
				{ return (*this->_node->val); }
			
			pointer operator->() const
				{ return  (this->_node->val); }

			bool operator==(const BST_iterator &cmping) const
			{
				if (this->_node == NULL && cmping._node == NULL)
					return (true);
				else if (this->_node == NULL || cmping._node == NULL)
					return (false);

				return (this->_node == cmping._node);
			}

			bool operator!=(const BST_iterator& cmping) const
				{ return (this->_node != cmping._node); }

			bool operator>=(const BST_iterator& cmping) const
				{ return (this->_node >= cmping._node); }

			bool operator<=(const BST_iterator& cmping) const
				{ return (this->_node <= cmping._node); }

			bool operator>(const BST_iterator& cmping) const
				{ return (this->_node > cmping._node); }

			bool operator<(const BST_iterator& cmping) const
				{ return (this->_node < cmping._node); }


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

			Node *	base() const
				{ return (this->_node); }
		private:
			Node	*_node;
	}; // class BST_iterator

/*
	template <class Node, class T, class Distance = __PTRDIFF_TYPE__>
	class BST_const_iterator
	{
		public:
			typedef T						value_type;
			typedef ptrdiff_t				difference_type;
			typedef value_type&				reference;
			typedef value_type*				pointer;

			typedef ft::bidirectional_iterator_tag				iterator_category;

			BST_const_iterator()
				{ this->_node = NULL; }

			BST_const_iterator(Node * node)
				{ this->_node = node; }

			BST_const_iterator(BST_const_iterator& bst_it)
				{ *this = bst_it; }
			
			BST_const_iterator (const BST_iterator<Node, T> &bst_it)
				{ this->_node = bst_it.base(); }
			
			BST_const_iterator &operator=(const BST_const_iterator &bst_it)
			{
				if (this == &bst_it)
					return (*this);

				this->_node = bst_it._node;

				return (*this);
			}			
	
			reference operator*() const
				{ return (*this->_node->val); }
			
			pointer operator->() const
				{ return  (this->_node->val); }

	
			BST_const_iterator(const BST_const_iterator &bst_it)
				{ *this = bst_it; }

			virtual ~BST_const_iterator() { return; }	

			friend bool operator==(const BST_const_iterator &cmping, const BST_const_iterator &cmped)
			{
				if (cmped._node == NULL && cmping._node == NULL)
					return (true);
				else if (cmped._node == NULL || cmping._node == NULL)
					return (false);

				return (cmping._node == cmped._node);
			}

			friend bool operator!=(const BST_const_iterator& cmped, const BST_const_iterator& cmping)
				{ return (cmped._node != cmping._node); }

			friend bool operator>=(const BST_const_iterator& cmped, const BST_const_iterator& cmping)
				{ return (cmped._node >= cmping._node); }

			friend bool operator<=(const BST_const_iterator& cmped, const BST_const_iterator& cmping)
				{ return (cmped._node <= cmping._node); }

			friend bool operator>(const BST_const_iterator& cmped, const BST_const_iterator& cmping)
				{ return (cmped._node > cmping._node); }

			friend bool operator<(const BST_const_iterator& cmped, const BST_const_iterator& cmping)
				{ return (cmped._node < cmping._node); }
			
			BST_const_iterator	&operator++(void)
			{
				this->_node = this->_node->successor(this->_node);
				return (*this);
			}

			BST_const_iterator	&operator--(void)
			{
				this->_node = this->_node->predecessor(this->_node);
				return (*this);
			}

			BST_const_iterator	operator++(int)
			{
				BST_const_iterator tmp(*this);
				operator++();
				return (tmp);
			}

			BST_const_iterator	operator--(int)
			{
				BST_const_iterator tmp(*this);
				operator--();
				return (tmp);
			}

			BST_const_iterator	&operator-(const int n)
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
			
			BST_const_iterator	&operator+(const int n)
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

			Node *	base() const
				{ return (this->_node); }
		private:
			Node	*_node;
	}; // class BST_const_iterator


	template <class Node, class Alloc>
	bool operator==(const BST_iterator<Node, Alloc> &cmping, const BST_const_iterator<Node, Alloc> &cmped)
	{
		if (cmped.base() == NULL && cmping.base() == NULL)
			return (true);
		else if (cmped.base() == NULL || cmping.base() == NULL)
			return (false);

		return (cmping.base() == cmped.base());
	}
	
	template <class Node, class Alloc>
	bool operator!=(const BST_iterator<Node, Alloc> &cmped, const BST_const_iterator<Node, Alloc> &cmping)
		{ return (cmped.base() != cmping.base()); }

	template <class Node, class Alloc>
	bool operator>=(const BST_iterator<Node, Alloc> &cmped, const BST_const_iterator<Node, Alloc> &cmping)
		{ return (cmped.base() >= cmping.base()); }

	template <class Node, class Alloc>
	bool operator<=(const BST_iterator<Node, Alloc> &cmped, const BST_const_iterator<Node, Alloc> &cmping)
		{ return (cmped.base() <= cmping.base()); }

	template <class Node, class Alloc>
	bool operator>(const BST_iterator<Node, Alloc> &cmped, const BST_const_iterator<Node, Alloc> &cmping)
		{ return (cmped.base() > cmping.base()); }

	template <class Node, class Alloc>
	bool operator<(const BST_iterator<Node, Alloc> &cmped, const BST_const_iterator<Node, Alloc> &cmping)
		{ return (cmped.base() < cmping.base()); }





	template <class Node, class Alloc>
	bool operator==(const BST_const_iterator<Node, Alloc> &cmping, const BST_iterator<Node, Alloc> &cmped)
	{
		if (cmped.base() == NULL && cmping.base() == NULL)
			return (true);
		else if (cmped.base() == NULL || cmping.base() == NULL)
			return (false);

		return (cmping.base() == cmped.base());
	}
	
	template <class Node, class Alloc>
	bool operator!=(const BST_const_iterator<Node, Alloc> &cmped, const BST_iterator<Node, Alloc> &cmping)
		{ return (cmped.base() != cmping.base()); }

	template <class Node, class Alloc>
	bool operator>=(const BST_const_iterator<Node, Alloc> &cmped, const BST_iterator<Node, Alloc> &cmping)
		{ return (cmped.base() >= cmping.base()); }

	template <class Node, class Alloc>
	bool operator<=(const BST_const_iterator<Node, Alloc> &cmped, const BST_iterator<Node, Alloc> &cmping)
		{ return (cmped.base() <= cmping.base()); }

	template <class Node, class Alloc>
	bool operator>(const BST_const_iterator<Node, Alloc> &cmped, const BST_iterator<Node, Alloc> &cmping)
		{ return (cmped.base() > cmping.base()); }

	template <class Node, class Alloc>
	bool operator<(const BST_const_iterator<Node, Alloc> &cmped, const BST_iterator<Node, Alloc> &cmping)
		{ return (cmped.base() < cmping.base()); }
		// -------------------------------------------------------- ITERATORS
*/










	// -------------------------------------------------------- CLASS MAP
	template <class Key, class T, class Compare = std::less<Key>,
				class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		class	Node;

		public :
			typedef T 														mapped_type;
			typedef Key														key_type;
			typedef ft::pair<const Key, T>									value_type;
			typedef Compare													key_compare;
			typedef Alloc													allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::size_type						size_type;
			typedef typename ft::BST_iterator<Node, value_type>					iterator;
			typedef typename ft::BST_iterator<Node, const value_type>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

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
			explicit map(const key_compare &comp = key_compare(),
					const allocator_type &alloc = allocator_type());
			explicit map(const ft::map<Key, T> &cp);
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
			const_iterator					begin(void) const;
			iterator						end(void);
			const_iterator					end(void) const;

			reverse_iterator				rbegin(void);
			const_reverse_iterator			rbegin(void) const;
			reverse_iterator				rend(void);
			const_reverse_iterator			rend(void) const;


			void	ft_break()
			{
				std::cout << "this is the break yo!" << std::endl;
				for (int i = 0; i < 10; i++);
			}

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
					bool			endpoint;

					bool	is_left() const
					{
						if (this->parent == NULL
							|| this == this->parent->right)
							return (false);
						return (true);
					}

					bool	is_right() const
					{
						if (this->parent == NULL
							|| this == this->parent->left)
							return (false);
						return (true);
					}

					bool	is_root() const
					{
						if (this->parent == NULL)
							return (true);
						return (false);
					}

					node	*sibling() const
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

					Node	*successor(node *x) const
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

					Node	*predecessor(node *x) const
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

					void	moveDown(Node *nParent)
					{
						if (parent != NULL)
						{
							if (this->is_left())
							{
								parent->left = nParent;
							}
							else
							{
								parent->right = nParent;
							}
						}
						nParent->parent = parent;
						parent = nParent;
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
			void	deleteNode(Node *v);
			Node	*BSTreplace(Node *x);
			void	swapValues(Node *u, Node *v);
			void	fixDoubleBlack(Node *x);
			Node	*searchTreeHelper(Node *node, const key_type &val) const;
			
			Node	*minimum(Node *node) const;
			Node	*maximum(Node *node) const;
			void	clearHelper(Node *x);
			void	endPointUpdate(void);
			void	basicInit(void);

			void	_cpy_content(map &src);
	}; // class map

template <class Key, class T, class Compare, class Alloc>
bool	operator==(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	if (lhs.size() != rhs.size())
		return false;
	return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

template <class Key, class T, class Compare, class Alloc>
bool	operator!=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	return !(lhs == rhs);
}

template <class Key, class T, class Compare, class Alloc>
bool	operator< (const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template <class Key, class T, class Compare, class Alloc>
bool	operator<=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	return !(rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool	operator> (const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	return (rhs < lhs);
}

template <class Key, class T, class Compare, class Alloc>
bool	operator>=(const map<Key, T, Compare, Alloc> &lhs,
					const map<Key, T, Compare, Alloc> &rhs) {
	return !(lhs < rhs);
}

template <class Key, class T, class Compare, class Alloc>
void	swap(map<Key, T, Compare, Alloc> &x, map<Key, T, Compare, Alloc> &y) {
	x.swap(y);
}


} // namespace ft

# include "map.ipp"

#endif
	