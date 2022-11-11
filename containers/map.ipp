#define ITERATOR	ft::map<key_type, mapped_type, key_compare, allocator_type>::iterator
#define MAP		ft::map<key_type, mapped_type, key_compare, allocator_type>

// CONSTRUCTS DESTRUCT
template<class key_type, class mapped_type, class key_compare, class allocator_type>
MAP::map(const key_compare &comp, const allocator_type &alloc)
{
	this->_alloc = alloc;
	this->_comp = comp;
	this->_root = this->TNULL;
	this->_nodesNbr = 0;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
MAP::map(const map<key_type, mapped_type> &cp)
{
	this->_alloc = cp->_alloc;
	this->_comp = cp->_comp;
	this->_nodesNbr = 0;
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
	this->insert(first, last);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
MAP	&MAP::operator=(const ft::map<key_type, mapped_type> &cpy)
{
	if (this->_root != TNULL)
		this->clear();

	this->_root = TNULL;
	this->_nodesNbr = 0;
	this->_alloc = cpy._alloc;
	this->_comp = cpy._comp;
	this->insert(cpy.begin(), cpy.end());
}

/*
template<class key_type, class mapped_type, class key_compare, class allocator_type>
MAP::~map()
	{ this->clear(); }
*/
// -------------------------------------------------------------------------------------


// ELEMENT ACCESS
template<class key_type, class mapped_type, class key_compare, class allocator_type>
mapped_type	&MAP::at(const key_type &key)
{
	return (this->operator[](key));
}
	
template<class key_type, class mapped_type, class key_compare, class allocator_type>
mapped_type	&MAP::operator[](const key_type &key)
{
	iterator	tmp = this->find(key);

	if (tmp == this->end())
		this->insert(std::make_pair(key, mapped_type()));
	tmp = this->find(key);
	return ((*tmp).second);
}
	


// CAPACITY
template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename allocator_type::size_type	MAP::size()
	{ return (this->_nodesNbr); }

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename allocator_type::size_type	MAP::max_size()
	{ std::distance(this->begin(), this->end()); }

template<class key_type, class mapped_type, class key_compare, class allocator_type>
bool	MAP::empty()
	{ return  (this->_root == TNULL); }




// MODIFIERS
template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	MAP::clear()
{
	erase(this->begin(), this->end());
	this->_nodesNbr = 0;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
std::pair<typename ITERATOR, bool>	MAP::insert(const value_type &val)
{
	Node	*node = new Node;
	Node	*y = NULL;
	Node	*x = this->_root;

	node->val = this->_alloc.allocate(1);
	this->_alloc.construct(node->val, val);	

	node->parent = NULL;
	node->left = TNULL;
	node->right = TNULL;
	node->color = RED;

	while (x != TNULL)
	{
		y = x;
		if (this->_comp((*node->val).first, (*x->val).first))
			x = x->left;
		else if ((*node->val).first == (*x->val).first)
			return ( std::make_pair(x, false) );
		else
			x = x->right;
	}

	this->_nodesNbr++;
	
	node->parent = y;

	if (y == NULL)
		_root = node;
	else if ( this->_comp((*node->val).first, (*y->val).first) )
		y->left = node;
	else
		y->right = node;

	if (node->parent == NULL)
	{
		node->color = BLACK;
		return ( std::make_pair(node, true) );
	}

	if (node->parent->parent == NULL)
		return ( std::make_pair(node, true) );

	insertFix(node);
	return (std::make_pair(node, true));
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
	if (this->_root != TNULL)
		this->clear();
	this->_alloc = x._alloc;
	this->_comp = x._comp;
	this->_root = TNULL;
	this->_nodesNbr = 0;
	this->insert(x.begin(), x.end());
}


template<class key_type, class mapped_type, class key_compare, class allocator_type>
size_t	MAP::erase(const key_type &key)
{
	Node	*z = TNULL;
	Node	*x;
	Node	*y;

	while (this->_root != TNULL)
	{
		if ( (*this->_root->val).first == key)
			z = this->_root;

		if ( (*this->_root->val).first <= key)
			this->_root = this->_root->right;
		else
			this->_root = this->_root->left;
	}

	if (z == TNULL)
		return (0);

	y = z;
	int y_original_color = y->color;
	if (z->left == TNULL)
	{
		x = z->right;
		rbTransplant(z, z->right);
	}
	else if (z->right == TNULL)
	{
		x = z->left;
		rbTransplant(z, z->left);
	}
	else
	{
		y = minimum(z->right);
		y_original_color = y->color;
		x = y->right;
		if (y->parent == z)
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

	if (y_original_color == 0)
		deleteFix(x);

	return (1);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	MAP::erase(ITERATOR first, ITERATOR second)
{
	while (first != second)
	{
		erase((*first->val).first);
		first++;
	}
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
	while (min->left != TNULL)
		min = min->right;
	return (min);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ITERATOR	MAP::end() const
{
	Node	*max;

	max = this->_root;
	while (max->right != TNULL)
		max = max->right;
	return (max);
}



// LOOKUP

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename allocator_type::size_type	MAP::count(const key_type &key) const
{
	iterator	tmp = this->find(key);

	if (tmp == this->end())
		return (0);
	return (1);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ITERATOR MAP::find(const key_type &k) const
	{ return searchTreeHelper(this->_root, k); }


//PRIVATE METHODS
template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	MAP::rbTransplant(Node *u, Node *v)
{
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

	while (x != this->_root && x->color == 0)
	{
		if (x == x->parent->left)
		{
			s = x->parent->right;
			if (s->color == 1)
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
					s->color = BLACK;
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
			if (u->color == RED)
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

			if (u->color == RED)
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
void	MAP::leftRotate(Node *x)
{
	Node	*y = x->right;

	x->right = y->left;
	if (y->left != TNULL)
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
	if (y->right != TNULL)
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
	while (node->left != TNULL)
		node = node->left;

	return node;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename MAP::Node	*MAP::searchTreeHelper(Node *node, const key_type &key) const
{
	if (node == TNULL || key == (*node->val).first)
		return node;

	if (key < (*node->val).first)
		return searchTreeHelper(node->left, key);

	return searchTreeHelper(node->right, key);
}
