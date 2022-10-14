
template<class value_type, class allocator_type>
typename ft::random_access_iterator<value_type>
	ft::vector<value_type, allocator_type>::begin(void)
{
	return (this->_start);
}

template<class value_type, class allocator_type>
typename ft::random_access_iterator<value_type>
	ft::vector<value_type, allocator_type>::end(void)
{
	return (this->_end);
}

template<class value_type, class allocator_type>
typename ft::random_access_iterator<const value_type>
	ft::vector<value_type, allocator_type>::begin(void) const
{
	return (this->_start);
}

template<class value_type, class allocator_type>
typename ft::random_access_iterator<const value_type>
	ft::vector<value_type, allocator_type>::end(void) const
{
	return (this->_end);
}

template<class value_type, class allocator_type>
typename ft::reverse_iterator<value_type>
	ft::vector<value_type, allocator_type>::rbegin(void)
{
	return (this->_end);
}

template<class value_type, class allocator_type>
typename ft::reverse_iterator<value_type>
	ft::vector<value_type, allocator_type>::rend(void)
{
	return (this->_start);
}

template<class value_type, class allocator_type>
typename ft::reverse_iterator<const value_type>
	ft::vector<value_type, allocator_type>::rbegin(void) const
{
	return (this->_end);
}

template<class value_type, class allocator_type>
typename ft::reverse_iterator<const value_type>
	ft::vector<value_type, allocator_type>::rend(void) const
{
	return (this->_start);
}
