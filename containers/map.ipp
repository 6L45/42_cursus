// CONSTRUCTS DESTRUCT
template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::map<key_type, mapped_type, key_compare, allocator_type>
	::map(const key_compare &comp, const allocator_type &alloc)
{
	this->_alloc = alloc;
	this->_comp = comp;
	this->basicInit();
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::map<key_type, mapped_type, key_compare, allocator_type>
	::map(const map<key_type, mapped_type> &cp)
{
	if (&cp == this)
		return;

	this->_alloc = cp._alloc;
	this->_comp = cp._comp;
	this->basicInit();

	this->insert(cp.begin(), cp.end());
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
template <class inputIt>
ft::map<key_type, mapped_type, key_compare, allocator_type>
	::map(inputIt first, inputIt last,
	const key_compare &comp, const allocator_type &alloc,
	typename ft::enable_if<!ft::is_integral<inputIt>::value, inputIt>::type *)
{
	this->_alloc = alloc;
	this->_comp = comp;
	this->basicInit();

	this->insert(first, last);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::map<key_type, mapped_type, key_compare, allocator_type>	&
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::operator=(const ft::map<key_type, mapped_type> &cpy)
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

template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::map<key_type, mapped_type, key_compare, allocator_type>::~map()
{
	clearHelper(this->_root);

	this->_alloc.destroy(this->_endPoint);
	this->_alloc.deallocate(this->_endPoint, 1);
}











// ELEMENT ACCESS
template<class key_type, class mapped_type, class key_compare, class allocator_type>
mapped_type	&ft::map<key_type, mapped_type, key_compare, allocator_type>
	::at(const key_type &key)
{
	iterator	tmp = this->find(key);

	if (tmp == NULL || tmp == this->_endPoint)
	{
		this->insert(ft::make_pair(key, mapped_type()));
		tmp = this->find(key);
	}

	return ((*tmp).second);
}
	
template<class key_type, class mapped_type, class key_compare, class allocator_type>
mapped_type	&ft::map<key_type, mapped_type, key_compare, allocator_type>
	::operator[](const key_type &key)
	{	return (this->at(key)); }











// CAPACITY
template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::size_type
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::size() const {
	return (this->_nodesNbr);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::size_type
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::max_size() const {
	return (this->_alloc.max_size());
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
bool	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::empty() const {
	return  (this->_root == NULL);
}






template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::clearHelper(Node *node)
{
	if (node == NULL || node == this->_endPoint)
		return;

	clearHelper(node->right);
	clearHelper(node->left);

	this->_alloc.destroy(node);
	this->_alloc.deallocate(node, 1);
}




// MODIFIERS
template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::clear()
{
	clearHelper(this->_root);

	this->_alloc.destroy(this->_endPoint);
	this->_alloc.deallocate(this->_endPoint, 1);

	this->basicInit();
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::pair<typename ft::map<key_type, mapped_type, key_compare, allocator_type>::iterator, bool>
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::insert(const value_type &val)
{
	pointer	node = this->_alloc.allocate(sizeof(Node));
	Node	tmp(val);
	this->_alloc.construct(node, tmp);
	Node	*y = NULL;
	Node	*x = this->_root;

	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;

	while (x != NULL && x != this->_endPoint)
	{
		y = x;
		if (this->_comp(node->val.first, x->val.first))
			x = x->left;
		else if (node->val.first == x->val.first)
		{
			this->_alloc.destroy(node);
			this->_alloc.deallocate(node, 1);

			return ( ft::make_pair(iterator(x), false) );
		}
		else
			x = x->right;
	}

	this->_nodesNbr++;
	node->parent = y;

	if (y == NULL || y == this->_endPoint)
		_root = node;
	else if ( this->_comp(node->val.first, y->val.first) )
		y->left = node;
	else
		y->right = node;

	if (node->parent == NULL)
	{
		node->color = BLACK;
		endPointUpdate();
		return ( ft::make_pair(iterator(node), true) );
	}

	if (node->parent->parent == NULL)
	{
		endPointUpdate();
		return ( ft::make_pair(iterator(node), true) );
	}
	
	insertFix(node);
	endPointUpdate();

	return (ft::make_pair(iterator(node), true));
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::iterator
ft::map<key_type, mapped_type, key_compare, allocator_type>
	::insert(iterator pos, const value_type &val)
{
	(void)pos;
	return (insert(val).first);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
template<class InputIterator>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::insert (InputIterator first, InputIterator last, typename ft::enable_if
				<!ft::is_integral<InputIterator>::value, InputIterator>::type *)
{
	while (first != last)
		insert(*first++);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::swap(map &x)
{
	map	tmp;

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


template<class key_type, class mapped_type, class key_compare, class allocator_type>
size_t	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::erase(const key_type &key)
{
	Node	*v = NULL;
	Node	*node = this->_root;

	while (node != NULL && node != this->_endPoint)
	{
		if (node->val.first == key)
		{
			v = node;
			break;
		}

		else if (this->_comp(node->val.first, key))
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

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::erase(iterator first, iterator second)
{
	ft::vector<key_type>	keys;

	while (first != second)
	{
		keys.push_back(first->first);
		first++;
	}
	for (size_t i = 0; i < keys.size(); i++)
		erase(keys[i]);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::erase(iterator pos) {
	erase((*pos).first);
}











// ft::map<key_type, mapped_type, key_compare, allocator_type>::iteratorS
template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::iterator
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::begin()
{
	if (this->empty())
		return (iterator(this->_endPoint));

	return (iterator(minimum(this->_root)));
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::const_iterator
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::begin() const
{
	if (this->empty())
		return (const_iterator(this->_endPoint));

	return (const_iterator(minimum(this->_root)));
}

template <class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::iterator
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::end() {
	return (iterator(this->_endPoint));
}

template <class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::const_iterator
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::end() const {
	return (const_iterator(this->_endPoint));
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::reverse_iterator
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::rend()
{
	if (this->empty())
		return (reverse_iterator(this->_endPoint));

	return (reverse_iterator(minimum(this->_root)));
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::const_reverse_iterator
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::rend() const
{
	if (this->empty())
		return (const_reverse_iterator(this->_endPoint));

	return (const_reverse_iterator(minimum(this->_root)));
}

template <class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::reverse_iterator
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::rbegin() {
	return (reverse_iterator(this->_endPoint));
}

template <class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::const_reverse_iterator
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::rbegin() const {
	return (const_reverse_iterator(this->_endPoint));
}









// LOOKUP
template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::allocator_type::size_type
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::count(const key_type &key) const
{
	if (this->find(key) == this->end())
		return (0);
	return (1);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::iterator
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::find(const key_type &k) {
	return searchTreeHelper(this->_root, k);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::const_iterator
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::find(const key_type &k) const {
	return searchTreeHelper(this->_root, k);
}


template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::iterator
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::lower_bound(const key_type &key)
{
	iterator	it = this->begin();
	iterator	end = this->end();
	
	while ( it != end && this->_comp(it->first, key) )
		it++;
	
	return (it);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::const_iterator
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::lower_bound(const key_type &key) const
{
	const_iterator	it = this->begin();
	const_iterator	end = this->end();
	
	while ( it != end && this->_comp((*it).first, key) )
		it++;
	
	return (it);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::iterator
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::upper_bound(const key_type &key)
{
	iterator	it = this->begin();
	iterator	end = this->end();

	while (it != end)
	{
		if (this->_comp(key, (*it).first))
			break;
		it++;
	}
	return (it);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::const_iterator
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::upper_bound(const key_type &key) const
{
	const_iterator	it = this->begin();
	const_iterator	end = this->end();

	while (it != end)
	{
		if (this->_comp(key, (*it).first))
			break;
		it++;
	}
	return (it);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::pair<typename ft::map<key_type, mapped_type, key_compare, allocator_type>::iterator,
		typename ft::map<key_type, mapped_type, key_compare, allocator_type>::iterator>
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::equal_range(const key_type &key) {
	return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::pair<typename ft::map<key_type, mapped_type, key_compare, allocator_type>::const_iterator,
		typename ft::map<key_type, mapped_type, key_compare, allocator_type>::const_iterator>
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::equal_range(const key_type &key) const {
	return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
}












//PRIVATE METHODS
template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::basicInit()
{
	this->_root = NULL;
	this->_endPoint = this->_alloc.allocate(sizeof(Node));
	this->_alloc.construct(this->_endPoint, Node());
	this->_endPoint->parent = NULL;
	this->_endPoint->right = NULL;
	this->_endPoint->left = NULL;
	this->_nodesNbr = 0;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::insertFix(Node *k)
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

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::fixDoubleBlack(Node *x)
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

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::leftRotate(Node *x)
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
void	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::rightRotate(Node *x)
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
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::Node*
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::minimum(Node *node) const
{
	while (node->left != NULL)
		node = node->left;

	return node;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::Node*
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::maximum(Node *node) const
{
	while (node->right != NULL && node->right != this->_endPoint)
		node = node->right;

	return node;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::Node*
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::searchTreeHelper(Node *node, const key_type &key) const
{
	if (node == NULL || node == this->_endPoint)
		return (this->_endPoint);
	if (key == node->val.first)
		return (node);

	if (this->_comp(key, node->val.first))
		return (searchTreeHelper(node->left, key));

	return searchTreeHelper(node->right, key);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::endPointUpdate()
{
	if (this->_root == NULL)
		return ;
	Node	*max = this->maximum(this->_root);

	max->right = this->_endPoint;
	this->_endPoint->parent = max;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::swapValues(Node *u, Node *v)
{
	pointer	temp;

	temp = u->val;
	u->val = v->val;
	v->val = temp;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::Node*
	ft::map<key_type, mapped_type, key_compare, allocator_type>
		::BSTreplace(Node *x)
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

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>
	::deleteNode(Node *rmNode)
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
	this->_alloc.destroy(rmNode);
	this->_alloc.deallocate(rmNode, 1);
}
