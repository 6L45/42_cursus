// MODIFIERS
template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::insert(std::pair<const key_type, mapped_type> val)
{
	Node *newNode = new Node(val);
	if (this->_root == NULL)
	{
		// when _root is null
		// simply insert value at _root
		newNode->color = BLACK;
		this->_root = newNode;
	}
	else
	{
		Node *temp = find(val);

		if (temp->val == val)
		{
			// return if value already exists
			return;
		}

		// if value is not found, search returns the node
		// where the value is to be inserted

		// connect new node to correct node
		newNode->parent = temp;

		if (val < temp->val)
			temp->left = newNode;
		else
			temp->right = newNode;

		// fix red red voilaton if exists
		fix_red_red(newNode);
	}
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::erase(std::pair<const key_type, mapped_type> val)
{
	if (this->_root == NULL)
		// Tree is empty
		return;

	Node *v = find(val), *u;

	if (v->val != val)
	{
		std::cout << "No node found to delete with value:" << val << std::endl;
		return;
	}

	delete_node(val);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::Node	*ft::map<key_type, mapped_type, key_compare, allocator_type>::find(std::pair<const key_type, mapped_type> val)
{
		Node *temp = this->_root;
		while (temp != NULL)
		{
			if (val < temp->val)
			{
				if (temp->left == NULL)
					break;
				else
					temp = temp->left;
			}
			else if (val == temp->val)
			{
				break;
			}
			else
			{
				if (temp->right == NULL)
					break;
				else
					temp = temp->right;
			}
		}
		return temp;
}

// CONSTRUCT DESTRUCT
template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::map<key_type, mapped_type, key_compare, allocator_type>::map(const key_compare &comp, const allocator_type &alloc)
{
/*	this->_alloc = alloc;
	pointer test = this->_alloc.allocate(sizeof(Node));
	Node	tmp(test);
*/
	this->_size = 0;
	const std::pair<const key_type, mapped_type> test("haha", 1);
	insert(test);
}

/*
template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::map<key_type, mapped_type, key_compare, allocator_type>::map(const ft::map<key_type, mapped_type> &cpy)
{
	this->_alloc = cpy._alloc;
//	this->insert(cp.begin(), cp.end());
}


template<class key_type, class mapped_type, class key_compare, class allocator_type>
template<class inputIt>
ft::map<key_type, mapped_type, key_compare, allocator_type>::map(inputIt first, inputIt last,
																const key_compare &comp,
																const allocator_type &alloc,
																typename ft::enable_if<!ft::is_integral<inputIt>::value, inputIt>::type *)
{
//	this->insert(first, last);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::map<key_type, mapped_type, key_compare, allocator_type>
	ft::map<key_type, mapped_type, key_compare, allocator_type>::operator=
												(const ft::map<key_type, mapped_type> &cpy)
{
	if (&cpy == this)
		return (*this);
	this->clear();
	this->insert(cpy.begin(), cpy.end());
	
	return (*this);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::map<key_type, mapped_type, key_compare, allocator_type>::~map()
{
//	this->clear();
}


// MODIFIERS
template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::Binary_search_tree<value_type, key_compare>::iterator
												insert(const ft::pair<key_type, mapped_type> &val)
{

}



template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::add
												(const ft::pair<key_type, mapped_type> &val)
{
	pointer	tmp_mem = this->_alloc.allocate(sizeof(_node));
	_node	tmp_node(tmp_mem);

	if (this->__root.this_mem == NULL)
	{
		this->__root = tmp_node;
		this->__root.color = BLACK;
		this->_size++;
		return;
	}
	add(this->__root, tmp_node);
	this->_size++;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::add
												(_node &parent, _node &new_node)
{
	// --|||||||||||-----------------------
//	if ((key_compare(new_node.val.first, parent.val.first)) > 0 ) // VOIR STD::LESS AND MODIF
	// --|||||||||||-----------------------
	if (true)
	{
		if (parent.right == NULL)
		{
			*parent.right = new_node;
			*new_node.parent = parent;
			new_node.pos = LEFT;
		}
		return add(*parent.right, new_node);
	}
	else
	{
		if (parent.left == NULL)
		{
			*parent.left = new_node;
			*new_node.parent = parent;
			new_node.pos = RIGHT;
		}
		return add(*parent.left, new_node);
	}
	check_colors(new_node);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::check_colors(_node &node)
{
	if (node.pos == _root)
		return;

	if (node.color == RED && node.parent->color == RED )
		correct_tree(node);
	check_colors(*node.parent);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::correct_tree(_node &node)
{
//	if (node.parent->pos == LEFT) // uncle is the right			/*             0 <- node.parent->parent                  */
//	{															/* node.      / \                                        */
//		if (node.parent->parent->right == NULL					/* parent -> O   O <- node.parent->parent->right (oncle) */
//			|| node.parent->parent->right->color == BLACK)		/*           |                                           */
//			return (rotate(node));								/*           O  <- node (right or left)                  */
//	
/*		if (node.parent->parent->right != NULL)
			node.parent->parent->right->color = BLACK;
		node.parent->parent->color = RED;
		node.parent->color = BLACK;
		return ;
	}
	else if (node.parent->pos == RIGHT)
	{
		if (node.parent->parent->left == NULL
		|| node.parent->parent->left->color == BLACK)
			return (rotate(node));
	}
	if (node.parent->parent->left != NULL)
		node.parent->parent->left->color = BLACK;
	node.parent->parent->color = RED;
	node.parent->color = BLACK;
	return;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::rotate(_node &node)
{
	if (node.pos == LEFT)
	{
		if (node.parent->pos == LEFT)
		{
			right_rotate(*node.parent->parent);
			node.color = RED;
			node.parent->color = BLACK;
			if (node.parent->right != NULL)
				node.parent->right->color = RED;
			return ;
		}
		else if (node.parent->pos == RIGHT)
		{
			right_left_rotate(*node.parent->parent);
			node.color = BLACK;
			node.right->color = RED;
			node.left->color = RED;
		}
	}
	else if (node.pos == RIGHT)
	{
		if (node.parent->pos == RIGHT)
		{
			left_rotate(*node.parent->parent);
			node.color = RED;
			node.parent->color = BLACK;
			if (node.parent->left != NULL)
				node.parent->left->color = RED;
			return ;
		}
		else if (node.parent->pos == LEFT)
		{
			left_right_rotate(*node.parent->parent);
			node.color = BLACK;
			node.left->color = RED;
			node.right->color = RED;
		}
	}
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::left_rotate(_node &node)
{
	_node tmp;

	tmp = *node.right;
	*node.right = tmp;

	if (node.right != NULL)
	{
		*node.right->parent = node;
		node.right->pos = RIGHT;
	}
	if (node.pos == _root)
	{
		node = tmp;
		this->__root = node;
		node.pos = _root;
		node.parent = NULL;
	}
	else
	{
		tmp.parent = node.parent;
		if (node.pos == LEFT)
		{
			tmp.pos = LEFT;
			*tmp.parent->left = tmp;
		}
		else if (node.pos == RIGHT)
		{
			tmp.pos = RIGHT;
			*tmp.parent->right = tmp;
		}
	}
	*tmp.left = node;
	node.left->pos = LEFT;
	*node.parent = tmp;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::right_rotate(_node &node)
{
	; // TO DO
}



template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::left_right_rotate(_node &node)
{
	left_rotate(*node.left);
	right_rotate(node);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::right_left_rotate(_node &node)
{
	right_rotate(*node.right);
	left_rotate(node);	
}


*/