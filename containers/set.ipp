#define ITERATOR				ft::set<value_type, key_compare, allocator_type>::iterator
#define CONST_ITERATOR			ft::set<value_type, key_compare, allocator_type>::const_iterator
#define REVERSE_ITERATOR		ft::set<value_type, key_compare, allocator_type>::reverse_iterator
#define REVERSE_CONST_ITERATOR	ft::set<value_type, key_compare, allocator_type>::const_reverse_iterator
#define SET						ft::set<value_type, key_compare, allocator_type>






// CONSTRUCTS DESTRUCT
template<class value_type, class key_compare, class allocator_type>
SET::set(const key_compare &comp, const allocator_type &alloc)
{
	this->_alloc = alloc;
	this->_comp = comp;
	this->basicInit();
}

template<class value_type, class key_compare, class allocator_type>
SET::set(const set<value_type> &cp)
{
	if (&cp == this)
		return;

	this->_alloc = cp._alloc;
	this->_comp = cp._comp;
	this->basicInit();

	this->insert(cp.begin(), cp.end());
}

template<class value_type, class key_compare, class allocator_type>
template <class inputIt>
SET::set(inputIt first, inputIt last,
	const key_compare &comp, const allocator_type &alloc,
	typename ft::enable_if<!ft::is_integral<inputIt>::value, inputIt>::type *)
{
	this->_alloc = alloc;
	this->_comp = comp;
	this->basicInit();

	this->insert(first, last);
}

template<class value_type, class key_compare, class allocator_type>
SET	&SET::operator=(const ft::set<value_type> &cpy)
{
	if (&cpy == this)
		return (*this);

	if (this->_root != NULL)
		this->clear();

	this->_alloc = cpy._alloc;
	this->_comp = cpy._comp;
	this->basicInit();

	this->insert(cpy.begin(), cpy.end());

	return (*this);
}

template<class value_type, class key_compare, class allocator_type>
SET::~set()
{
	clearHelper(this->_root);

	this->_alloc.destroy(this->_endPoint->val);
	this->_alloc.deallocate(this->_endPoint->val, 1);
	delete this->_endPoint;	
}











// ELEMENT ACCESS
template<class value_type, class key_compare, class allocator_type>
value_type	&SET::at(const value_type &key)
{
	iterator	tmp = this->find(key);

	if (tmp == NULL || tmp == this->_endPoint)
	{
		this->insert(key);
		tmp = this->find(key);
	}

	return (*tmp);
}
	
template<class value_type, class key_compare, class allocator_type>
value_type	&SET::operator[](const value_type &key)
	{	return (this->at(key)); }











// CAPACITY
template<class value_type, class key_compare, class allocator_type>
typename allocator_type::size_type	SET::size() const
	{	return (this->_nodesNbr); }

template<class value_type, class key_compare, class allocator_type>
typename allocator_type::size_type	SET::max_size() const
	{	return (this->_alloc.max_size() / 2); }

template<class value_type, class key_compare, class allocator_type>
bool	SET::empty() const
	{	return  (this->_root == NULL); }






template<class value_type, class key_compare, class allocator_type>
void	SET::clearHelper(Node *node)
{
	if (node == NULL || node == this->_endPoint)
		return;

	clearHelper(node->right);
	clearHelper(node->left);

	this->_alloc.destroy(node->val);
	this->_alloc.deallocate(node->val, 1);
	delete node;
}




// MODIFIERS
template<class value_type, class key_compare, class allocator_type>
void	SET::clear()
{
	clearHelper(this->_root);

	this->_alloc.destroy(this->_endPoint->val);
	this->_alloc.deallocate(this->_endPoint->val, 1);
	delete this->_endPoint;

	this->basicInit();
}

template<class value_type, class key_compare, class allocator_type>
ft::pair<typename ITERATOR, bool>	SET::insert(const value_type &val)
{
	Node	*node = new Node;
	Node	*y = NULL;
	Node	*x = this->_root;

	node->val = this->_alloc.allocate(1);
	this->_alloc.construct(node->val, val);	

	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->endpoint = false;
	node->color = RED;

	while (x != NULL && x != this->_endPoint)
	{
		y = x;
		if (this->_comp(*node->val, *x->val))
			x = x->left;
		else if (*node->val == *x->val)
		{
			this->_alloc.destroy(node->val);
			this->_alloc.deallocate(node->val, 1);
			delete node;

			return ( ft::make_pair(SET::iterator(x), false) );
		}
		else
			x = x->right;
	}

	this->_nodesNbr++;
	node->parent = y;

	if (y == NULL || y == this->_endPoint)
		_root = node;
	else if ( this->_comp(*node->val, *y->val))
		y->left = node;
	else
		y->right = node;

	if (node->parent == NULL)
	{
		node->color = BLACK;
		endPointUpdate();
		return ( ft::make_pair(SET::iterator(node), true) );
	}

	if (node->parent->parent == NULL)
	{
		endPointUpdate();
		return ( ft::make_pair(SET::iterator(node), true) );
	}
	
	insertFix(node);
	endPointUpdate();

	return (ft::make_pair(SET::iterator(node), true));
}

template<class value_type, class key_compare, class allocator_type>
typename ITERATOR	SET::insert(ITERATOR pos, const value_type &val)
{
	(void)pos;
	return (insert(val).first);
}

template<class value_type, class key_compare, class allocator_type>
template<class InputIterator>
void	SET::insert (InputIterator first, InputIterator last, typename ft::enable_if
				<!ft::is_integral<InputIterator>::value, InputIterator>::type *)
{
	while (first != last)
	{
		insert(*first);
		first++;
	}
}

template<class value_type, class key_compare, class allocator_type>
void	SET::swap(typename SET &x)
{
	typename SET	tmp;

	tmp._alloc = x._alloc;
	tmp._comp = x._comp;
	tmp._root = x._root;
	Node * tmpEndPoint = x._endPoint;
	tmp._nodesNbr = x._nodesNbr;

	x._alloc = this->_alloc;
	x._comp = this->_comp;
	x._root = this->_root;
	x._endPoint = this->_endPoint;
	x._nodesNbr = this->_nodesNbr;

	this->_alloc = tmp._alloc;
	this->_comp = tmp._comp;
	this->_root = tmp._root;
	this->_endPoint = tmpEndPoint;
	this->_nodesNbr = tmp._nodesNbr;

	tmp._root = NULL;
}


template<class value_type, class key_compare, class allocator_type>
size_t	SET::erase(const value_type &key)
{
	Node	*v = NULL;
	Node	*node = this->_root;

	while (node != NULL && node != this->_endPoint)
	{
		if (*node->val == key)
		{
			v = node;
			break;
		}

		else if (this->_comp(*node->val, key))
			node = node->right;
		else
			node = node->left;
	}
	
	if (v == NULL || v == this->_endPoint)
		return (0);

	deleteNode(v);
	this->_nodesNbr--;

	endPointUpdate();
	return (1);
}

template<class value_type, class key_compare, class allocator_type>
void	SET::erase(ITERATOR first, ITERATOR second)
{
	ft::vector<value_type>	keys;

	while (first != second)
	{
		keys.push_back(*first);
		first++;
	}
	for (size_t i = 0; i < keys.size(); i++)
		erase(keys[i]);
}

template<class value_type, class key_compare, class allocator_type>
void	SET::erase(ITERATOR pos)
	{	erase(*pos); }











// ITERATORS
template<class value_type, class key_compare, class allocator_type>
typename ITERATOR	SET::begin()
{
	if (this->empty())
		return (iterator(this->_endPoint));

	return (iterator(minimum(this->_root)));
}

template<class value_type, class key_compare, class allocator_type>
typename CONST_ITERATOR	SET::begin() const
{
	if (this->empty())
		return (const_iterator(this->_endPoint));

	return (const_iterator(minimum(this->_root)));
}

template <class value_type, class key_compare, class allocator_type>
typename ITERATOR SET::end()
{
	return (iterator(this->_endPoint));
}

template <class value_type, class key_compare, class allocator_type>
typename CONST_ITERATOR SET::end() const
{
	return (const_iterator(this->_endPoint));
}

template<class value_type, class key_compare, class allocator_type>
typename REVERSE_ITERATOR	SET::rend()
{
	if (this->empty())
		return (reverse_iterator(this->_endPoint));

	return (reverse_iterator(minimum(this->_root)));
}

template<class value_type, class key_compare, class allocator_type>
typename REVERSE_CONST_ITERATOR	SET::rend() const
{
	if (this->empty())
		return (const_reverse_iterator(this->_endPoint));

	return (const_reverse_iterator(minimum(this->_root)));
}

template <class value_type, class key_compare, class allocator_type>
typename REVERSE_ITERATOR SET::rbegin()
{
	return (reverse_iterator(this->_endPoint));
}

template <class value_type, class key_compare, class allocator_type>
typename REVERSE_CONST_ITERATOR SET::rbegin() const
{
	return (const_reverse_iterator(this->_endPoint));
}









// LOOKUP
template<class value_type, class key_compare, class allocator_type>
typename allocator_type::size_type	SET::count(const value_type &key) const
{
	if (this->find(key) == this->end())
		return (0);
	return (1);
}

template<class value_type, class key_compare, class allocator_type>
typename ITERATOR SET::find(const value_type &k)
	{	return searchTreeHelper(this->_root, k); }

template<class value_type, class key_compare, class allocator_type>
typename CONST_ITERATOR SET::find(const value_type &k) const
	{	return searchTreeHelper(this->_root, k); }


template<class value_type, class key_compare, class allocator_type>
typename ITERATOR SET::lower_bound(const value_type &key)
{
	typename SET::iterator	it = this->begin();
	typename SET::iterator	end = this->end();
	
	while ( it != end && this->_comp(*it, key) )
		it++;
	
	return (it);
}

template<class value_type, class key_compare, class allocator_type>
typename CONST_ITERATOR SET::lower_bound(const value_type &key) const
{
	typename SET::const_iterator	it = this->begin();
	typename SET::const_iterator	end = this->end();
	
	while ( it != end && this->_comp((*it), key) )
		it++;
	
	return (it);
}

template<class value_type, class key_compare, class allocator_type>
typename ITERATOR SET::upper_bound(const value_type &key)
{
	typename SET::iterator	it = this->begin();
	typename SET::iterator	end = this->end();

	while (it != end)
	{
		if (this->_comp(key, (*it)))
			break;
		it++;
	}
	return (it);
}

template<class value_type, class key_compare, class allocator_type>
typename CONST_ITERATOR SET::upper_bound(const value_type &key) const
{
	typename SET::const_iterator	it = this->begin();
	typename SET::const_iterator	end = this->end();

	while (it != end)
	{
		if (this->_comp(key, (*it)))
			break;
		it++;
	}
	return (it);
}

template<class value_type, class key_compare, class allocator_type>
ft::pair<typename ITERATOR, typename ITERATOR>	SET::equal_range(const value_type &key)
	{	return (ft::make_pair(this->lower_bound(key), this->upper_bound(key))); }

template<class value_type, class key_compare, class allocator_type>
ft::pair<typename CONST_ITERATOR, typename CONST_ITERATOR>
	SET::equal_range(const value_type &key) const
		{	return (ft::make_pair(this->lower_bound(key), this->upper_bound(key))); }












//PRIVATE METHODS
template<class value_type, class key_compare, class allocator_type>
void	SET::basicInit()
{
	this->_root = NULL;
	this->_endPoint = new Node;
	this->_endPoint->val = this->_alloc.allocate(1);
	this->_alloc.construct(this->_endPoint->val, value_type());	
	this->_endPoint->endpoint = true;
	this->_endPoint->parent = NULL;
	this->_endPoint->right = NULL;
	this->_endPoint->left = NULL;
	this->_nodesNbr = 0;
}

template<class value_type, class key_compare, class allocator_type>
void	SET::insertFix(Node *k)
{
	Node *u;
	
	while (k->parent->color == RED)
	{
		if (k->parent == k->parent->parent->right)
		{
			u = k->parent->parent->left;
			if (u && u != this->_endPoint && u->color == RED)
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

			if (u && u != this->_endPoint && u->color == RED)
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

template<class value_type, class key_compare, class allocator_type>
void	SET::fixDoubleBlack(Node *x)
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
				if (sibling->left != NULL && sibling->left->color == RED)
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

template <class value_type, class key_compare, class allocator_type>
void	SET::leftRotate(Node *x)
{
	// new parent will be node's right child
	Node *nParent = x->right;

	// update root if current node is root
	if (x == _root)
		_root = nParent;

	x->moveDown(nParent);

	// connect x with new parent's left element
	x->right = nParent->left;
	// connect new parent's left element with node
	// if it is not null
	if (nParent->left != NULL)
		nParent->left->parent = x;

	// connect new parent with x
	nParent->left = x;
}

template <class value_type, class key_compare, class allocator_type>
void	SET::rightRotate(Node *x)
{
	// new parent will be node's left child
	Node *nParent = x->left;

	// update root if current node is root
	if (x == _root)
		_root = nParent;

	x->moveDown(nParent);

	// connect x with new parent's right element
	x->left = nParent->right;
	// connect new parent's right element with node
	// if it is not null
	if (nParent->right != NULL && nParent->right != this->_endPoint)
		nParent->right->parent = x;

	// connect new parent with x
	nParent->right = x;
}

/*
template<class value_type, class key_compare, class allocator_type>
void	SET::leftRotate(Node *x)
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

template<class value_type, class key_compare, class allocator_type>
void	SET::rightRotate(Node *x)
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
*/

template<class value_type, class key_compare, class allocator_type>
typename SET::Node	*SET::minimum(Node *node) const
{
	while (node->left != NULL)
		node = node->left;

	return node;
}

template<class value_type, class key_compare, class allocator_type>
typename SET::Node	*SET::maximum(Node *node) const
{
	while (node->right != NULL && node->right != this->_endPoint)
		node = node->right;

	return node;
}

template<class value_type, class key_compare, class allocator_type>
typename SET::Node	*SET::searchTreeHelper(Node *node, const value_type &key) const
{
	if (node == NULL || node == this->_endPoint)
		return (this->_endPoint);
	if (key == *node->val)
		return (node);

	if (this->_comp(key, *node->val))
		return (searchTreeHelper(node->left, key));

	return searchTreeHelper(node->right, key);
}

template<class value_type, class key_compare, class allocator_type>
void	SET::endPointUpdate()
{
	if (this->_root == NULL)
		return ;
	Node	*max = this->maximum(this->_root);

	max->right = this->_endPoint;
	this->_endPoint->parent = max;
}

template<class value_type, class key_compare, class allocator_type>
void	SET::swapValues(Node *u, Node *v)
{
	pointer	temp;

	temp = u->val;
	u->val = v->val;
	v->val = temp;
}

template<class value_type, class key_compare, class allocator_type>
typename SET::Node	*SET::BSTreplace(Node *x)
{
	// when node have 2 children
	if (x->left != NULL && x->right != NULL && x->right != this->_endPoint)
	{
		Node	*temp = x;

		while (temp->left != NULL)
			temp = temp->left;

		return temp;
	}
	// when leaf
	if (x->left == NULL
		&& (x->right == NULL || x->right == this->_endPoint))
		return NULL;

	// when single child
	if (x->left != NULL)
		return x->left;
	else if (x->right != NULL && x->right != this->_endPoint)
		return x->right;
	else
		return NULL;
}

template<class value_type, class key_compare, class allocator_type>
void	SET::deleteNode(Node *rmNode)
{
	Node	*replaceNode = NULL;
	Node	**rmPlace = &this->_root;

	if (rmNode->parent)
		rmPlace = (rmNode->parent->left == rmNode ? &rmNode->parent->left : &rmNode->parent->right);
	if (rmNode->left == NULL && rmNode->right == NULL)
		;
	else if (rmNode->left == NULL) // left == NULL && right != NULL
		replaceNode = rmNode->right;
	else // left != NULL && right ?= NULL
	{
		replaceNode = maximum(rmNode->left);
		if (replaceNode != rmNode->left)
			if ((replaceNode->parent->right = replaceNode->left))
				replaceNode->left->parent = replaceNode->parent;
	}
	if (replaceNode)
	{
		replaceNode->parent = rmNode->parent;
		if (rmNode->left && rmNode->left != replaceNode)
		{
			replaceNode->left = rmNode->left;
			replaceNode->left->parent = replaceNode;
		}
		if (rmNode->right && rmNode->right != replaceNode)
		{
			replaceNode->right = rmNode->right;
			replaceNode->right->parent = replaceNode;
		}
	}

	*rmPlace = replaceNode;
	this->_alloc.destroy(rmNode->val);
	this->_alloc.deallocate(rmNode->val, 1);
	delete rmNode;
}
