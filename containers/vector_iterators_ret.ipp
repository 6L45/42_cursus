
template<class value_type, class allocator_type>
typename ft::vector<value_type, allocator_type>::iterator
	ft::vector<value_type, allocator_type>::begin(void)
{
	return (this->_start);
}

template<class value_type, class allocator_type>
typename ft::vector<value_type, allocator_type>::iterator
	ft::vector<value_type, allocator_type>::end(void)
{
	return (this->_end);
}

template<class value_type, class allocator_type>
typename ft::vector<value_type, allocator_type>::const_iterator
	ft::vector<value_type, allocator_type>::begin(void) const
{
	return (this->_start);
}

template<class value_type, class allocator_type>
typename ft::vector<value_type, allocator_type>::const_iterator
	ft::vector<value_type, allocator_type>::end(void) const
{
	return (this->_end);
}

template<class value_type, class allocator_type>
typename ft::reverse_iterator<typename ft::vector<value_type, allocator_type>::iterator>
	ft::vector<value_type, allocator_type>::rbegin(void)
{
	return (ft::reverse_iterator<typename ft::vector<value_type, allocator_type>::iterator>(this->_end));
}

template<class value_type, class allocator_type>
typename ft::reverse_iterator<typename ft::vector<value_type, allocator_type>::iterator>
	ft::vector<value_type, allocator_type>::rend(void)
{
	return (ft::reverse_iterator<typename ft::vector<value_type, allocator_type>::iterator>(this->_start));
}

template<class value_type, class allocator_type>
typename ft::reverse_iterator<typename ft::vector<value_type, allocator_type>::const_iterator>
	ft::vector<value_type, allocator_type>::rbegin(void) const
{
	return (ft::reverse_iterator<typename ft::vector<value_type, allocator_type>::const_iterator>(this->_end));
}

template<class value_type, class allocator_type>
typename ft::reverse_iterator<typename ft::vector<value_type, allocator_type>::const_iterator>
	ft::vector<value_type, allocator_type>::rend(void) const
{
	return (ft::reverse_iterator<typename ft::vector<value_type, allocator_type>::const_iterator>(this->_start));
}

template<class value_type, class allocator_type>
template<class inputIt>
size_t	ft::vector<value_type, allocator_type>::__itLen(inputIt first, inputIt last)
{

	size_t	i = 0;
	inputIt	fcopy = first;
	inputIt	lcopy = last;

	while (fcopy != lcopy)
	{
		fcopy++;
		i++;
	}
	return (i);
}
