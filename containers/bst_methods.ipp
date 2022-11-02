
template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::left_rotate(Node *x)
{
	Node	*nParent = x->right;

	if (x == this->_root)
		this->_root = nParent;
	x->move_down(nParent);
	
	// connect x with new parent's left element
	x->right = nParent->left;
	// connect new parent's left element with node
	// if it is not null
	if (nParent->left != NULL)
		nParent->left->parent = x;

	// connect new parent with x
	nParent->left = x;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::right_rotate(Node *x)
{
	// new parent will be node's left child
	Node *nParent = x->left;

	// update this->_root if current node is this->_root
	if (x == this->_root)
		this->_root = nParent;

	x->move_down(nParent);

	// connect x with new parent's right element
	x->left = nParent->right;
	// connect new parent's right element with node
	// if it is not null
	if (nParent->right != NULL)
		nParent->right->parent = x;

	// connect new parent with x
	nParent->right = x;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::swap_colors(Node *x1, Node *x2)
{
	COLOR temp;
	temp = x1->color;
	x1->color = x2->color;
	x2->color = temp;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::swap_values(Node *u, Node *v)
{
	int temp;
	temp = u->val;
	u->val = v->val;
	v->val = temp;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::fix_red_red(Node *x)
{
	// if x is this->_root color it black and return
	if (x == this->_root)
	{
		x->color = BLACK;
		return;
	}

	// initialize parent, grandparent, uncle
	Node *parent = x->parent, *grandparent = parent->parent,
		 *uncle = x->uncle();

	if (parent->color != BLACK)
	{
		if (uncle != NULL && uncle->color == RED)
		{
			// uncle red, perform recoloring and recurse
			parent->color = BLACK;
			uncle->color = BLACK;
			grandparent->color = RED;
			fix_red_red(grandparent);
		}
		else
		{
			// Else perform LR, LL, RL, RR
			if (parent->is_on_left())
			{
				if (x->is_on_left())
				{
					// for left right
					swap_colors(parent, grandparent);
				}
				else
				{
					left_rotate(parent);
					swap_colors(x, grandparent);
				}
				// for left left and left right
				right_rotate(grandparent);
			}
			else
			{
				if (x->is_on_left())
				{
					// for right left
					right_rotate(parent);
					swap_colors(x, grandparent);
				}
				else
				{
					swap_colors(parent, grandparent);
				}

				// for right right and right left
				left_rotate(grandparent);
			}
		}
	}
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::Node	*
		ft::map<key_type, mapped_type, key_compare, allocator_type>::successor(Node *x)
{
	Node *temp = x;

	while (temp->left != NULL)
		temp = temp->left;

	return temp;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::Node *
		ft::map<key_type, mapped_type, key_compare, allocator_type>::BSTreplace(Node *x)
{
	// when node have 2 children
	if (x->left != NULL and x->right != NULL)
		return successor(x->right);

	// when leaf
	if (x->left == NULL and x->right == NULL)
		return NULL;

	// when single child
	if (x->left != NULL)
		return x->left;
	else
		return x->right;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::delete_node(Node *v)
{
	Node *u = BSTreplace(v);

	// True when u and v are both black
	bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
	Node *parent = v->parent;

	if (u == NULL)
	{
		// u is NULL therefore v is leaf
		if (v == this->_root)
		{
			// v is this->_root, making this->_root null
			this->_root = NULL;
		}
		else
		{
			if (uvBlack)
			{
				// u and v both black
				// v is leaf, fix double black at v
				fix_double_black(v);
			}
			else
			{
				// u or v is red
				if (v->sibling() != NULL)
					// sibling is not null, make it red"
					v->sibling()->color = RED;
			}

			// delete v from the tree
			if (v->is_on_left())
			{
				parent->left = NULL;
			}
			else
			{
				parent->right = NULL;
			}
		}
		delete v;
		return;
	}

	if (v->left == NULL or v->right == NULL)
	{
		// v has 1 child
		if (v == this->_root)
		{
			// v is this->_root, assign the value of u to v, and delete u
			v->val = u->val;
			v->left = v->right = NULL;
			delete u;
		}
		else
		{
			// Detach v from tree and move u up
			if (v->is_on_left())
			{
				parent->left = u;
			}
			else
			{
				parent->right = u;
			}
			delete v;
			u->parent = parent;
			if (uvBlack)
			{
				// u and v both black, fix double black at u
				fix_double_black(u);
			}
			else
			{
				// u or v red, color u black
				u->color = BLACK;
			}
		}
		return;
	}

	// v has 2 children, swap values with successor and recurse
	swap_values(u, v);
	delete_node(u);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::fix_double_black(Node *x)
{
	if (x == this->_root)
		// Reached this->_root
		return;

	Node *sibling = x->sibling(), *parent = x->parent;
	if (sibling == NULL)
	{
		// No sibiling, double black pushed up
		fix_double_black(parent);
	}
	else
	{
		if (sibling->color == RED)
		{
			// Sibling red
			parent->color = RED;
			sibling->color = BLACK;
			if (sibling->is_on_left())
			{
				// left case
				right_rotate(parent);
			}
			else
			{
				// right case
				left_rotate(parent);
			}
			fix_double_black(x);
		}
		else
		{
			// Sibling black
			if (sibling->has_red_child())
			{
				// at least 1 red children
				if (sibling->left != NULL and sibling->left->color == RED)
				{
					if (sibling->is_on_left())
					{
						// left left
						sibling->left->color = sibling->color;
						sibling->color = parent->color;
						right_rotate(parent);
					}
					else
					{
						// right left
						sibling->left->color = parent->color;
						right_rotate(sibling);
						left_rotate(parent);
					}
				}
				else
				{
					if (sibling->is_on_left())
					{
						// left right
						sibling->right->color = parent->color;
						left_rotate(sibling);
						right_rotate(parent);
					}
					else
					{
						// right right
						sibling->right->color = sibling->color;
						sibling->color = parent->color;
						left_rotate(parent);
					}
				}
				parent->color = BLACK;
			}
			else
			{
				// 2 black children
				sibling->color = RED;
				if (parent->color == BLACK)
					fix_double_black(parent);
				else
					parent->color = BLACK;
			}
		}
	}
}
