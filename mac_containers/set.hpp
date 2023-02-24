#ifndef SET_HPP
# define SET_HPP

# include <cstddef>

# include "utils.hpp"
# include "BST_iterator.hpp"
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
	template <class T, class Compare = std::less<T>,
				class Alloc = std::allocator<T> >
	class set
	{
		class	Node;
		typedef typename	Alloc::template rebind<Node>::other						Allocator;

		public :
			typedef T 														value_type;
			typedef Compare													key_compare;
			typedef Allocator												allocator_type;
			typedef typename allocator_type::reference						reference;
			typedef typename allocator_type::const_reference				const_reference;
			typedef typename allocator_type::pointer						pointer;
			typedef typename allocator_type::const_pointer					const_pointer;
			typedef typename allocator_type::size_type						size_type;
			typedef typename ft::BST_iterator<Node, const value_type>		iterator;
			typedef typename ft::BST_iterator<Node, const value_type>		const_iterator;
			typedef typename ft::reverse_iterator<iterator>					reverse_iterator;
			typedef typename ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class set;

				public:
					bool	operator() (const value_type& lhs, const value_type& rhs) const
						{ return (comp(lhs, rhs)); }

				protected:
					key_compare					comp;

					value_compare(Compare c)
						{ this->comp = c; }
			};

		// CONSTRUCT DESTRUCT
			template<class inputIt>
			set(inputIt first, inputIt last,
				const key_compare &comp = key_compare(), const allocator_type &alloc = allocator_type(),
				typename ft::enable_if<!ft::is_integral<inputIt>::value, inputIt>::type * = NULL);
			set(const key_compare &comp = key_compare(),
					const allocator_type &alloc = allocator_type());
			set(const ft::set<T> &cp);
			virtual ~set();

			set &operator=(const ft::set<T> &cpy);


		//ELEMENT ACCESS
			value_type						&at(const value_type &key);
			value_type						&operator[](const value_type &key);

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
			size_t							erase(const	value_type &k);
			void							swap(set &x);

		//LOOKUP
			size_type						count(const value_type &key) const;
			iterator						find(const value_type &key);
			const_iterator					find (const value_type& k) const;
			iterator						lower_bound(const value_type &key);
			const_iterator					lower_bound (const value_type& k) const;
			iterator						upper_bound(const value_type &key);
			const_iterator					upper_bound (const value_type& k) const;
			ft::pair<iterator, iterator>				equal_range(const value_type &key);
			ft::pair<const_iterator, const_iterator>	equal_range (const value_type& k) const;

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

		private:

			class Node
			{
				public:

					value_type		val;
					COLOR			color;
					Node			*left;
					Node			*right;
					Node			*parent;

					Node() {}
					Node(const value_type &value) : val(value)
						{ this->color = RED; }
					virtual ~Node() {}

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

					Node	*sibling() const
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

					Node	*successor(Node *x) const
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

					Node	*predecessor(Node *x) const
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
			pointer					_root;
			pointer					_endPoint;
			size_t					_nodesNbr;

			void	insertFix(Node *node);
			void	leftRotate(Node *node);
			void	rightRotate(Node *node);
			void	rbTransplant(Node *u, Node *v);
			void	deleteNode(Node *v);
			Node	*BSTreplace(Node *x);
			void	swapValues(Node *u, Node *v);
			void	fixDoubleBlack(Node *x);
			Node	*searchTreeHelper(Node *node, const value_type &val) const;
			
			Node	*minimum(Node *node) const;
			Node	*maximum(Node *node) const;
			void	clearHelper(Node *x);
			void	endPointUpdate(void);
			void	basicInit(void);

			void	_cpy_content(set &src);

	}; // class set

	template <class T, class Compare, class Alloc>
	bool	operator==(const set<T, Compare, Alloc> &lhs,
						const set<T, Compare, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
	
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Compare, class Alloc>
	bool	operator!=(const set<T, Compare, Alloc> &lhs,
						const set<T, Compare, Alloc> &rhs)
		{ return !(lhs == rhs); }

	template <class T, class Compare, class Alloc>
	bool	operator< (const set<T, Compare, Alloc> &lhs,
						const set<T, Compare, Alloc> &rhs)
		{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }

	template <class T, class Compare, class Alloc>
	bool	operator<=(const set<T, Compare, Alloc> &lhs,
						const set<T, Compare, Alloc> &rhs)
		{ return !(rhs < lhs); }

	template <class T, class Compare, class Alloc>
	bool	operator> (const set<T, Compare, Alloc> &lhs,
						const set<T, Compare, Alloc> &rhs)
		{ return (rhs < lhs); }

	template <class T, class Compare, class Alloc>
	bool	operator>=(const set<T, Compare, Alloc> &lhs,
						const set<T, Compare, Alloc> &rhs)
		{ return !(lhs < rhs); }

	template <class T, class Compare, class Alloc>
	void	swap(set<T, Compare, Alloc> &x, set<T, Compare, Alloc> &y)
		{ x.swap(y); }

} // namespace ft

# include "set.ipp"

#endif
	