
template<class value_type, class allocator_type>
ft::vector<value_type, allocator_type>::vector(const allocator_type &alloc)
{
	this->_alloc = alloc;
	this->_start = NULL;
	this->_end = NULL;
	this->_end_capacity = NULL;
}

template<class value_type, class allocator_type>
ft::vector<value_type, allocator_type>::vector(const ft::vector<value_type> &cp)
{
	this->_alloc = cp._alloc;
	this->_start = NULL;
	this->_end = NULL;
	this->_end_capacity = NULL;
	
	this->insert(this->begin(), cp.begin(), cp.end());
}

/*
template<class value_type, class allocator_type>
ft::vector<value_type, allocator_type>::vector(std::initializer_list<value_type> lst)
{
	this->_start = this->_alloc.allocate(lst.size() + 1);
	this->_end = this->_start + (lst.size());
	this->_end_capacity = this->_end;

	int	i = 0;
	for (typename std::initializer_list<value_type>::iterator it = lst.begin();
			it != lst.end(); it++)
	{
		this->_alloc.construct(this->_start + i, *it);
		i++;
	}
}
*/

template<class value_type, class allocator_type>
template<class inputIt>
ft::vector<value_type, allocator_type>::vector(inputIt first, inputIt last,
	typename ft::enable_if<!ft::is_integral<inputIt>::value, inputIt>::type *)
{
	size_t	input_size = __itLen(first, last);

	this->_start = this->_alloc.allocate(input_size + 1);
	this->_end = this->_start + input_size;
	this->_end_capacity = this->_end;

	std::copy(first, last, this->_start);
}

template<class value_type, class allocator_type>
ft::vector<value_type, allocator_type>	&ft::vector<value_type, allocator_type>::operator=
	(const ft::vector<value_type, allocator_type> &cpy)
{
	if (cpy == *this)
		return (*this);
	
	this->clear();

	if (this->_start)
		this->_alloc.deallocate(this->_start, this->capacity());
	this->_start = this->_alloc.allocate(cpy.capacity());
	std::copy(cpy.begin(), cpy.end(), this->_start);
	this->_end = this->_start + cpy.size();
	this->_end_capacity = this->_start + cpy.capacity();
	
	return (*this);
}

template<class value_type, class allocator_type>
ft::vector<value_type, allocator_type>::vector(const size_t count,
												value_type val, const allocator_type &alloc)
{
	this->_alloc = alloc;
	this->_start = this->_alloc.allocate(count + 1);
	this->_end = this->_start + count;
	this->_end_capacity = this->_end;

	for (size_t i = 0; i < count; i++)
		this->_alloc.construct(this->_start + i, val);
}

template<class value_type, class allocator_type>
ft::vector<value_type, allocator_type>::~vector()
{
	if (!this->_start)
		return;
	
	for (pointer bgin = this->_start; bgin != this->_end; bgin++)
		this->_alloc.destroy(bgin);

	this->_alloc.deallocate(this->_start, this->capacity() - 3);
}
