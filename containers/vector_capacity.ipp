
template<class value_type, class allocator_type>
bool	ft::vector<value_type, allocator_type>::empty() const
{
	if (this->_start == NULL || !this->size())
		return (true);
	return (false);
}

template<class value_type, class allocator_type>
typename allocator_type::size_type
	ft::vector<value_type, allocator_type>::size() const
	{ return (this->_end - this->_start); }

template<class value_type, class allocator_type>
void	ft::vector<value_type, allocator_type>::reserve(size_t n)
{
	if (this->_end_capacity && n <= this->capacity() - 1)
		return ;

	typename allocator_type::size_type 	old_size = this->size();
	pointer	new_start = this->_alloc.allocate(n + 1);

	for (size_t i = 0; i < old_size; i++)
	{
		this->_alloc.construct(new_start + i, *(this->_start + i));
		this->_alloc.destroy(this->_start + i);
	}
	if (this->_start)
		this->_alloc.deallocate(this->_start, this->capacity());
	this->_start = new_start;
	this->_end = this->_start + old_size;
	this->_end_capacity = this->_start + n;
}

template<class value_type, class allocator_type>
typename allocator_type::size_type
	ft::vector<value_type, allocator_type>::capacity() const
	{ return (this->_end_capacity - this->_start); }

template<class value_type, class allocator_type>
typename allocator_type::size_type
	ft::vector<value_type, allocator_type>::max_size() const
	{ return (allocator_type().max_size()); }
