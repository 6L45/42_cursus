#ifndef BST_ITERATOR_HPP
#define BST_ITERATOR_HPP

namespace ft
{
	class bidirectional_iterator_tag {};

	template <class Node, class T>
	class BST_iterator
	{
		public:
			typedef T								value_type;
			typedef ptrdiff_t						difference_type;
			typedef value_type&						reference;
			typedef value_type*						pointer;

			typedef ft::bidirectional_iterator_tag	iterator_category;

			BST_iterator()
				{ this->_node = NULL; }
			BST_iterator(Node * node)
				{ this->_node = node; }
			BST_iterator(const BST_iterator& bst_it)
				{ *this = bst_it; }
			
			BST_iterator	&operator=(const BST_iterator &bst_it)
			{
				if (this == &bst_it)
					return (*this);

				this->_node = bst_it._node;

				return (*this);
			}			
			operator	BST_iterator<Node, const T>(void) const
				{ return BST_iterator<Node, const T>(this->_node); }

			virtual ~BST_iterator() {}

			reference		operator*() const
				{ return (this->_node->val); }
			pointer			operator->() const
				{ return  (&this->_node->val); }
			bool			operator==(const BST_iterator &cmping) const
			{
				if (this->_node == NULL && cmping._node == NULL)
					return (true);
				else if (this->_node == NULL || cmping._node == NULL)
					return (false);

				return (this->_node == cmping._node);
			}
			bool			operator!=(const BST_iterator& cmping) const
				{ return (this->_node != cmping._node); }
			bool			operator>=(const BST_iterator& cmping) const
				{ return (this->_node >= cmping._node);	}
			bool			operator<=(const BST_iterator& cmping) const
				{ return (this->_node <= cmping._node); }
			bool			operator>(const BST_iterator& cmping) const
				{ return (this->_node > cmping._node); }
			bool			operator<(const BST_iterator& cmping) const
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

		private:
			Node	*_node;

	}; // class BST_iterator

} // namespace ft

#endif
