
template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::map<key_type, mapped_type, key_compare, allocator_type>::Node::Node(value_type &val)
{
	this->parent = NULL;
	this->left = NULL;
	this->right = NULL;
	color = RED;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::Node	*ft::map<key_type, mapped_type, key_compare, allocator_type>::Node::uncle()
{
	if (parent == NULL || parent->parent == NULL)
		return (NULL);

	// if parent is left uncle is right
	if (parent->is_on_left())
		return (parent->parent->right);
	else
		return (parent->parent->left);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
typename ft::map<key_type, mapped_type, key_compare, allocator_type>::Node	*ft::map<key_type, mapped_type, key_compare, allocator_type>::Node::sibling()
{
	if (parent == NULL)
		return (NULL);
	if (is_on_left())
		return (parent->right);
	return (parent->left);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
void	ft::map<key_type, mapped_type, key_compare, allocator_type>::Node::move_down(Node *nParent)
{
	if (parent != NULL)
	{
		if (is_on_left())
			parent->left = nParent;
		else
			parent->right = nParent;
	}
	nParent->parent = parent;
	parent = nParent;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
bool	ft::map<key_type, mapped_type, key_compare, allocator_type>::Node::has_red_child()
{
	return ( (left != NULL && left->color == RED)
			|| (right != NULL && right->color == RED) );
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
bool	ft::map<key_type, mapped_type, key_compare, allocator_type>::Node::is_on_left()
	{	return (this == parent->left); }

