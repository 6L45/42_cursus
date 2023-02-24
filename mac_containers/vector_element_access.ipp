
template<class value_type, class allocator_type>
typename	allocator_type::reference	ft::vector<value_type, allocator_type>::at
																		(const unsigned int n)
{
	if (this->size() < n)
		throw std::out_of_range ("");
	else 
		return (*(this->_start + n));
}

template<class value_type, class allocator_type>
typename	allocator_type::reference	ft::vector<value_type, allocator_type>::front()
	{ return (*this->_start); }

template<class value_type, class allocator_type>
typename	allocator_type::reference	ft::vector<value_type, allocator_type>::back()
	{ return (*(this->_end - 1)); }

template<class value_type, class allocator_type>
typename	allocator_type::reference	ft::vector<value_type, allocator_type>::operator[]
																				(const size_t n)
	{ return (*(this->_start + n)); }

template<class value_type, class allocator_type>
typename	allocator_type::const_reference	ft::vector<value_type, allocator_type>::at
																		(const unsigned int n) const
{
	if (this->size() < n)
		throw std::out_of_range ("");
	else 
		return (*(this->_start + n));
}

template<class value_type, class allocator_type>
typename	allocator_type::const_reference	ft::vector<value_type, allocator_type>::front() const
	{ return (*this->_start); }

template<class value_type, class allocator_type>
typename	allocator_type::const_reference	ft::vector<value_type, allocator_type>::back() const
	{ return (*(this->_end - 1)); }

template<class value_type, class allocator_type>
typename	allocator_type::const_reference	ft::vector<value_type, allocator_type>::operator[]
																					(const size_t n) const
	{ return (*(this->_start + n)); }
