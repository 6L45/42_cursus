#define ITERATOR	ft::map<key_type, mapped_type, key_compare, allocator_type>::iterator
#define CONST_ITERATOR	ft::map<key_type, mapped_type, key_compare, allocator_type>::const_iterator
#define MAP		ft::map<key_type, mapped_type, key_compare, allocator_type>






// CONSTRUCTS DESTRUCT
template<class key_type, class mapped_type, class key_compare, class allocator_type>
MAP::map(const key_compare &comp, const allocator_type &alloc)
{
	this->_alloc = alloc;
	this->_comp = comp;
	this->_root = NULL;
	this->_nodesNbr = 0;
	this->_endPoint = new Node;
	this->_endPoint->endpoint = true;
	this->_endPoint->parent = NULL;
	this->_endPoint->right = NULL;
	this->_endPoint->left = NULL;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
MAP::map(const map<key_type, mapped_type> &cp)
{
	if (&cp == this)
		return;

	this->_alloc = cp->_alloc;
	this->_comp = cp->_comp;
	this->_nodesNbr = 0;
	this->_endPoint = new Node;
	this->_endPoint->endpoint = true;
	this->_endPoint->parent = NULL;
	this->_endPoint->right = NULL;
	this->_endPoint->left = NULL;
	this->insert(cp.begin(), cp.end());
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
template <class inputIt>
MAP::map(inputIt first, inputIt last,
	const key_compare &comp, const allocator_type &alloc,
	typename ft::enable_if<!ft::is_integral<inputIt>::value, inputIt>::type *)
{
	this->_alloc = alloc;
	this->_comp = comp;
	this->_nodesNbr = 0;
	this->_endPoint = new Node;
	this->_endPoint->endpoint = true;
	this->_endPoint->parent = NULL;
	this->_endPoint->right = NULL;
	this->_endPoint->left = NULL;
	this->insert(first, last);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
MAP	&MAP::operator=(const ft::map<key_type, mapped_type> &cpy)
{
	if (&cpy == this)
		return (*this);

	if (this->_root != NULL)
		this->clear();

	this->_root = NULL;
	this->_nodesNbr = 0;
	this->_alloc = cpy._alloc;
	this->_comp = cpy._comp;
	this->_endPoint = new Node;
	this->_endPoint->endpoint = true;
	this->_endPoint->parent = NULL;
	this->_endPoint->right = NULL;
	this->_endPoint->left = NULL;
	this->insert(cpy.begin(), cpy.end());
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
MAP::~map()
{
	this->clear();
}












// ELEMENT ACCESS
template<class key_type, class mapped_type, class key_compare, class allocator_type>
mapped_type	&MAP::at(const key_type &key)
{
	iterator	tmp = this->find(key);

	if (tmp == this->end())
	{
		this->insert(ft::make_pair(key, mapped_type()));
		tmp = this->find(key);
	}
	return ((*tmp)->second);
}
	
template<class key_type, class mapped_type, class key_compare, class allocator_type>
mapped_type	&MAP::operator[](const key_type &key)
	{ return (this->at(key)); }











// CAPACITY
template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename allocator_type::size_type	MAP::size() const
	{ return (this->_nodesNbr); }

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename allocator_type::size_type	MAP::max_size() const
	{ return (this->_alloc.max_size()); }

template<class key_type, class mapped_type, class key_compare, class allocator_type>
bool	MAP::empty() const
	{ return  (this->_root == NULL); }






template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	MAP::clearHelper(Node *nod)
{
	if (nod == NULL || nod == this->_endPoint)
		return;
	clearHelper(nod->right);
	clearHelper(nod->left);
	
	this->_alloc.destroy(nod->val);
	this->_alloc.deallocate(nod->val, 1);
	delete nod;

}




// MODIFIERS
template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	MAP::clear()
{
/*	
	clearHelper(this->_root);
	delete this->_endPoint;
*/
	std::vector<key_type>	test;
	for (typename ft::map<key_type, mapped_type>::iterator it = this->begin(); it != this->end(); it++)
		test.push_back( (*it).first );
	
	for (auto el : test)
		this->erase(el);
	delete this->_endPoint;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::pair<typename ITERATOR, bool>	MAP::insert(const value_type &val)
{
	Node	*node = new Node;
	Node	*y = NULL;
	Node	*x = this->_root;

	node->val = this->_alloc.allocate(1);
	this->_alloc.construct(node->val, val);	

	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->color = RED;

	while (x != NULL && x != this->_endPoint)
	{
		y = x;
		if (this->_comp((*node->val).first, (*x->val).first))
			x = x->left;
		else if ((*node->val).first == (*x->val).first)
		{
			this->_alloc.destroy(node->val);
			this->_alloc.deallocate(node->val, 1);
			delete node;

			return ( ft::make_pair(MAP::iterator(x), false) );
		}
		else
			x = x->right;
	}

	this->_nodesNbr++;
	node->parent = y;

	if (y == NULL || y == this->_endPoint)
		_root = node;
	else if ( this->_comp((*node->val).first, (*y->val).first) )
		y->left = node;
	else
		y->right = node;

	if (node->parent == NULL)
	{
		node->color = BLACK;
		return ( ft::make_pair(MAP::iterator(node), true) );
	}

	if (node->parent->parent == NULL)
		return ( ft::make_pair(MAP::iterator(node), true) );

	insertFix(node);
	endPointUpdate();

	return (ft::make_pair(MAP::iterator(node), true));
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ITERATOR	MAP::insert(ITERATOR pos, const value_type &val)
{
	(void)pos;
	return (insert(val));
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
template<class InputIterator>
void	MAP::insert (InputIterator first, InputIterator last, typename ft::enable_if
				<!ft::is_integral<InputIterator>::value, InputIterator>::type *)
{
	while (first != last)
	{
		insert(*first);
		first++;
	}
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	MAP::swap(typename MAP &x)
{
	if (this->_root != NULL)
		this->clear();

	typename MAP	tmp(x);
	x = *this;
	*this = tmp;
}


template<class key_type, class mapped_type, class key_compare, class allocator_type>
size_t	MAP::erase(const key_type &key)
{
	Node	*z = NULL;
	Node	*node = this->_root;
	Node	*x;
	Node	*y;

	while (node != NULL && node != this->_endPoint)
	{
		if ((*node->val).first == key)
		{
			z = node;
			break;
		}

		else if (this->_comp((*node->val).first, key))
			node = node->right;
		else
			node = node->left;
	}

	if (z == NULL || z == this->_endPoint)
		return (0);

	y = z;
	int y_original_color = y->color;

	if (!z->left && !z->right && z->right != this->_endPoint)
	{
		if (z->color == BLACK)
			this->fixDoubleBlack(z);
		
		if (z->left)
			z->left->parent = NULL;
		if (z->right)
			z->right->parent = NULL;
		if (z->parent)
		{
			if (z->is_left())
				z->parent->left = NULL;
			else
				z->parent->right = NULL;
		}

		this->_alloc.destroy(z->val);
		this->_alloc.deallocate(z->val, 1);
		delete z;
		this->_nodesNbr--;

		return (1);
	}

	else if (z->left == NULL)
	{
		x = z->right;
		rbTransplant(z, z->right);
	}
	else if (z->right == NULL || z->right == this->_endPoint)
	{
		x = z->left;
		rbTransplant(z, z->left);
	}
	else
	{
		y = minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z && x)
			x->parent = y;
		else
		{
			rbTransplant(y, y->right);
			y->right = z->right;
			y->right->parent = y;
		}

		rbTransplant(z, y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	this->_alloc.destroy(z->val);
	this->_alloc.deallocate(z->val, 1);

	delete z;
	this->_nodesNbr--;

	if (y_original_color == BLACK)
		deleteFix(x);

	return (1);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	MAP::erase(ITERATOR first, ITERATOR second)
{
	ft::vector<key_type>	keys;

	while (first != second)
	{
		keys.push_back((*first).first);
		first++;
	}
	for (int i = 0; i < keys.size(); i++)
		erase(keys[i]);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	MAP::erase(ITERATOR pos)
	{ erase((*pos->val).first); }











// ITERATORS
template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ITERATOR	MAP::begin()
{
	Node	*min;

	min = this->_root;
	while (min->left != NULL)
		min = min->left;
	return (min);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename CONST_ITERATOR	MAP::begin() const
{
	Node	*min;

	min = this->_root;
	while (min->left != NULL)
		min = min->left;
	return (min);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ITERATOR	MAP::end()
{
	Node	*max;

	max = this->_root;
	while (max->right != NULL && max->right != this->_endPoint)
		max = max->right;
	return (this->_endPoint);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename CONST_ITERATOR	MAP::end() const
{
	Node	*max;

	max = this->_root;
	while (max->right != NULL && max->right != this->_endPoint)
		max = max->right;
	return (this->_endPoint);
}









// LOOKUP
template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename allocator_type::size_type	MAP::count(const key_type &key) const
{
	if (this->find(key) == this->end())
		return (0);
	return (1);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ITERATOR MAP::find(const key_type &k)
	{ return searchTreeHelper(this->_root, k); }

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename CONST_ITERATOR MAP::find(const key_type &k) const
	{ return searchTreeHelper(this->_root, k); }


template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ITERATOR MAP::lower_bound(const key_type &key)
{
	typename MAP::iterator	it = this->begin();
	typename MAP::iterator	end = this->end();
	
	while ( it != end && this->_comp((*it).first, key) )
		it++;
	
	return (it);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename CONST_ITERATOR MAP::lower_bound(const key_type &key) const
{
	typename MAP::iterator	it = this->begin();
	typename MAP::iterator	end = this->end();
	
	while ( it != end && this->_comp((*it).first, key) )
		it++;
	
	return (it);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ITERATOR MAP::upper_bound(const key_type &key)
{
	typename MAP::iterator	it = this->begin();
	typename MAP::iterator	end = this->end();

	while ( it != end && this->_comp(key, (*it).first) )
		it++;
	
	return (it);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename CONST_ITERATOR MAP::upper_bound(const key_type &key) const
{
	typename MAP::iterator	it = this->begin();
	typename MAP::iterator	end = this->end();

	while ( it != end && this->_comp(key, (*it).first) )
		it++;
	
	return (it);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::pair<typename ITERATOR, typename ITERATOR>	MAP::equal_range(const key_type &key)
	{ return (ft::make_pair(this->lower_bound(key), this->upper_bound(key))); }

template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::pair<typename CONST_ITERATOR, typename CONST_ITERATOR>
	MAP::equal_range(const key_type &key) const
		{ return (ft::make_pair(this->lower_bound(key), this->upper_bound(key))); }












//PRIVATE METHODS
template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	MAP::rbTransplant(Node *u, Node *v)
{
	if (!u || !v)
		return ;
	if (u->parent == NULL)
		this->_root = v;
	else if (u == u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	v->parent = u->parent;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	MAP::deleteFix(Node *x)
{
	Node	*s;

	while (x != this->_root && x->color == BLACK)
	{
		if (x == x->parent->left)
		{
			s = x->parent->right;
			if (s->color == RED)
			{
				s->color = BLACK;
				x->parent->color = RED;
				leftRotate(x->parent);
				s = x->parent->right;
			}

			if (s->left->color == BLACK && s->right->color == BLACK)
			{
				s->color = RED;
				x = x->parent;
			}
			else
			{
				if (s->right->color == BLACK)
				{
					s->left->color = BLACK;
					s->color = RED;
					rightRotate(s);
					s = x->parent->right;
				}

				s->color = x->parent->color;
				x->parent->color = BLACK;
				s->right->color = BLACK;
				leftRotate(x->parent);
				x = this->_root;
			}
		}
		else
		{
			s = x->parent->left;
			if (s->color == RED)
			{
				s->color = BLACK;
				x->parent->color = RED;
				rightRotate(x->parent);
				s = x->parent->left;
			}

			if (s->right->color == BLACK && s->right->color == BLACK)
			{
				s->color = RED;
				x = x->parent;
			}
			else
			{
				if (s->left->color == BLACK)
				{
					s->right->color = BLACK;
					s->color = RED;
					leftRotate(s);
					s = x->parent->left;
				}

				s->color = x->parent->color;
				x->parent->color = BLACK;
				s->left->color = BLACK;
				rightRotate(x->parent);
				x = this->_root;
			}
		}
	}
	x->color = BLACK;
}


template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	MAP::insertFix(Node *k)
{
	Node *u;
	
	while (k->parent->color == RED)
	{
		if (k->parent == k->parent->parent->right)
		{
			u = k->parent->parent->left;
			if (u && u->color == RED)
			{
				u->color = BLACK;
				k->parent->color = BLACK;
				k->parent->parent->color = RED;
				k = k->parent->parent;
			}
			else
			{
				if (k == k->parent->left)
				{
					k = k->parent;
					rightRotate(k);
				}
				k->parent->color = BLACK;
				k->parent->parent->color = RED;
				leftRotate(k->parent->parent);
			}
		}
		else
		{
			u = k->parent->parent->right;

			if (u && u->color == RED)
			{
				u->color = BLACK;
				k->parent->color = BLACK;
				k->parent->parent->color = RED;
				k = k->parent->parent;
			}
			else
			{
				if (k == k->parent->right)
				{
					k = k->parent;
					leftRotate(k);
				}
				k->parent->color = BLACK;
				k->parent->parent->color = RED;
				rightRotate(k->parent->parent);
			}
		}
		if (k == _root)
			break;
	}

	_root->color = BLACK;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	MAP::fixDoubleBlack(Node *x)
{
	if (x == this->_root)
		return;

	Node *sibling = x->sibling();
	Node *parent = x->parent;
	if (sibling == NULL || sibling == this->_endPoint)
		fixDoubleBlack(parent);
	else
	{
		if (sibling->color == RED)
		{
			parent->color = RED;
			sibling->color = BLACK;
			if (sibling->is_left())
				rightRotate(parent);
			else
				leftRotate(parent);
			fixDoubleBlack(x);
		}
		else
		{
			// Sibling black
			if ( (sibling->left && sibling->left->color == RED) 
				|| (sibling->right && sibling->right != this->_endPoint
					&& sibling->right->color == RED) )
			{
				// at least 1 red children
				if (sibling->left != NULL and sibling->left->color == RED)
				{
					if (sibling->is_left())
					{
						// left left
						sibling->left->color = sibling->color;
						sibling->color = parent->color;
						rightRotate(parent);
					}
					else
					{
						// right left
						sibling->left->color = parent->color;
						rightRotate(sibling);
						leftRotate(parent);
					}
				}
				else
				{
					if (sibling->is_left())
					{
						// left right
						sibling->right->color = parent->color;
						leftRotate(sibling);
						rightRotate(parent);
					}
					else
					{
						// right right
						sibling->right->color = sibling->color;
						sibling->color = parent->color;
						leftRotate(parent);
					}
				}
				parent->color = BLACK;
			}
			else
			{
				// 2 black children
				sibling->color = RED;
				if (parent->color == BLACK)
					fixDoubleBlack(parent);
				else
					parent->color = BLACK;
			}
		}
	}
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	MAP::leftRotate(Node *x)
{
	Node	*y = x->right;

	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	y->parent = x->parent;
	
	if (x->parent == NULL)
		this->_root = y;
	else if (x == x->parent->left)
		x->parent->left = y;
	else
		x->parent->right = y;

	y->left = x;
	x->parent = y;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	MAP::rightRotate(Node *x)
{
	Node	*y = x->left;

	x->left = y->right;
	if (y->right != NULL && y->right != this->_endPoint)
		y->right->parent = x;
	
	y->parent = x->parent;
	
	if (x->parent == NULL)
		this->_root = y;
	else if (x == x->parent->right)
		x->parent->right = y;
	else
		x->parent->left = y;
	
	y->right = x;
	x->parent = y;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename MAP::Node	*MAP::minimum(Node *node)
{
	while (node->left != NULL)
		node = node->left;

	return node;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename MAP::Node	*MAP::maximum(Node *node)
{
	while (node->right != NULL && node->right != this->_endPoint)
		node = node->right;

	return node;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename MAP::Node	*MAP::searchTreeHelper(Node *node, const key_type &key) const
{
	if (node == NULL || key == (*node->val).first)
		return node;

	if (this->_comp(key, (*node->val).first))
		return searchTreeHelper(node->left, key);

	return searchTreeHelper(node->right, key);
}


template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	MAP::endPointUpdate()
{
	Node	*max = this->maximum(this->_root);

	max->right = this->_endPoint;
	this->_endPoint->parent = max;
}
