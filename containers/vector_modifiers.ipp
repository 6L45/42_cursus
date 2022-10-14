
template<class value_type, class allocator_type>
void	ft::vector<value_type, allocator_type>::assign(size_t count, const value_type &val)
{
	this->clear();

	size_t	cont_size = this->capacity();

	if (cont_size < count)
	{
		if (this->_start)
			this->_alloc.deallocate(this->_start, this->capacity());
		this->_start = this->_alloc.allocate(count + 1);
		this->_end = this->_start + count;
		this->_end_capacity = this->_end;
	}
	else if (cont_size >= count)
		this->_end = this->_start + count;
	
	for (size_t i = 0; i < count; i++)
		this->_alloc.construct(this->_start + i, val);
}

template<class value_type, class allocator_type>
template<class inputIt>
void	ft::vector<value_type, allocator_type>::assign(inputIt first, inputIt last,
				typename ft::enable_if<!ft::is_integral<inputIt>::value,inputIt>::type *)
{
	this->clear();

	size_t	input_size = last - first;
	size_t	cont_size = this->capacity();

	if (cont_size < input_size)
	{
		if (this->_start)
			this->_alloc.deallocate(this->_start, this->capacity());
		this->_start = this->_alloc.allocate(input_size + 1);
		this->_end = this->_start + input_size;
		this->_end_capacity = this->_end;
	}
	else if (cont_size >= input_size)
		this->_end = this->_start + input_size;

	std::copy(first, last, this->_start);
}

template<class value_type, class allocator_type>
void	ft::vector<value_type, allocator_type>::clear()
{
	if (!this->_start)
		return ;
	
	for (pointer it = this->_start; it != this->_end; it++)
		this->_alloc.destroy(it);
	this->_end = this->_start;
}

template<class value_type, class allocator_type>
typename ft::random_access_iterator<value_type>
	ft::vector<value_type, allocator_type>::insert(typename ft::random_access_iterator<value_type> pos,
													size_t n, const value_type &val)
{
	const size_t	dist = pos - this->_start;
	size_t			p = 0;

	if (this->size() + n > this->capacity())
	{
		ft::vector<value_type>	tmp(this->size() + n);

		for (size_t i = 0; i < dist; i++, p++)
			tmp[p] = *(this->_start + i);
		for (size_t i = 0; i < n; i++, p++)
			tmp[p] = val;
		for (size_t i = 0; this->begin() + dist + i != this->end() ; i++, p++)
			tmp[p] = *(this->begin() + dist + i);

		this->swap(tmp);
	
		return (this->_start + dist);
	}
	else
	{
		ft::vector<value_type>	tmp(this->size() - dist);

		for (size_t i = 0; this->_start + dist + i < this->_end; i++, p++)
			tmp[p] = *(this->_start + dist + i);

		for (size_t i = 0; i < n; i++)
		{
			this->_alloc.destroy(this->_start + dist + i);
			if (i < n)
				this->_alloc.construct(this->_start + dist + i, val);
			this->_end = this->_start + dist + i + 1;
		}
		for (size_t i = 0; tmp.begin() + i < tmp.end(); i++)
			this->push_back(*(tmp.begin() + i));
		return (pos);
	}
}

template<class value_type, class allocator_type>
template <class inputIt>
void	ft::vector<value_type, allocator_type>::insert(typename ft::random_access_iterator<value_type> pos,
														inputIt first, inputIt last, typename ft::enable_if
														<!ft::is_integral<inputIt>::value, inputIt>::type*)
{
	size_t	dist = pos - this->_start;
	size_t	offset = last - first;
	size_t	p = 0;

	if (this->size() + offset > this->capacity())
	{
		ft::vector<value_type>	tmp(this->size() + offset);
		for (size_t i = 0; i < dist; i++, p++)
			tmp[p] = *(this->_start + i);
		for (;first != last; first++, p++)
			tmp[p] = *first;
		for (size_t i = 0; this->_start + dist + i < this->_end; i++, p++)
			tmp[p] = *(this->_start + dist + i);
		
		this->swap(tmp);
	}
	else
	{
		ft::vector<value_type>	tmp(this->size() - dist);

		for (size_t i = 0; this->_start + dist + i < this->_end; i++, p++)
			tmp[p] = *(this->_start + dist + i);

		for (size_t i = 0; first < last; i++, first++)
		{
			this->_alloc.destroy(this->_start + dist + i);
			if (first < last)
				this->_alloc.construct(this->_start + dist + i, *first);
			this->_end = this->_start + dist + i + 1;
		}
		for (size_t i = 0; tmp.begin() + i < tmp.end(); i++)
			this->push_back(*(tmp.begin() + i));
	}
}

template<class value_type, class allocator_type>
typename ft::random_access_iterator<value_type>
	ft::vector<value_type, allocator_type>::insert(typename ft::random_access_iterator<value_type> pos,
													const value_type &val)
{
	return (this->insert(pos, 1, val));
}

template<class value_type, class allocator_type>
typename ft::random_access_iterator<value_type>
	ft::vector<value_type, allocator_type>::erase(typename ft::random_access_iterator<value_type> pos)
{
	size_t	i = 0;
	size_t	dist = pos - this->_start;

	for (; this->_start + dist + i < this->_end; i++)
	{
		this->_alloc.destroy(this->_start + dist + i);
		if (this->_start + dist + i + 1 != this->_end)
			this->_alloc.construct(this->_start + dist + i, *(this->_start + dist + i + 1));
	}
	this->_end--; 
	return (pos);
}

template<class value_type, class allocator_type>
typename ft::random_access_iterator<value_type>
	ft::vector<value_type, allocator_type>::erase(typename ft::random_access_iterator<value_type> first,
													typename ft::random_access_iterator<value_type> last)
{
	size_t	i = 0;
	size_t	j = 0;
	size_t	distbegin = first - this->_start;
	size_t	distend = last - this->_start;

	for (; this->_start + distbegin + i < this->_end; i++)
	{
		this->_alloc.destroy(this->_start + distbegin + i);
		if (this->_start + distend + j != this->_end)
		{
			this->_alloc.construct(this->_start + distbegin + i, *(this->_start + distend + j));
			j++;
		}
	}
	this->_end -= last - first; 
	return (first);
}

template<class value_type, class allocator_type>
void	ft::vector<value_type, allocator_type>::pop_back(void)
{
	if (this->_end == this->_start)
		return ;
	this->_alloc.destroy(&this->back());
	this->_end--;
}

template<class value_type, class allocator_type>
void	ft::vector<value_type, allocator_type>::resize(size_t n, value_type val)
{
	if (n > this->max_size())
		throw(std::length_error(""));
	else if (n < this->size())
	{
		while (this->size() > n)
		{
			this->_end--;
			this->_alloc.destroy(this->_end);
		}
	}
	else
		this->insert(this->end(), n - this->size(), val);
}

template <class value_type, class allocator_type>
void ft::vector<value_type, allocator_type>::push_back(value_type val)
{
	if (!this->_start)
	{
		this->_start = this->_alloc.allocate(2);
		this->_alloc.construct(this->_start, val);
		this->_end = this->_start + 1;
		this->_end_capacity = this->_end;
	}
	else if (this->_end >= this->_end_capacity)
	{
		typename allocator_type::size_type	old_size = this->size();
		pointer new_start = this->_alloc.allocate((old_size * 2) + 1);
		
		for (size_t i = 0; i < old_size; i++)
		{
			this->_alloc.construct(new_start + i, *(this->_start + i));
			this->_alloc.destroy(this->_start + i);
		}
		this->_alloc.deallocate(this->_start, this->capacity());
		this->_start = new_start;
		this->_alloc.construct(this->_start + old_size, val);
		this->_end = this->_start + old_size + 1;
		this->_end_capacity = this->_start + (old_size * 2);
	}
	else
	{
		this->_alloc.construct(this->_start + this->size(), val);
		this->_end++;
	}
}

template<class value_type, class allocator_type>
void	ft::vector<value_type, allocator_type>::swap(ft::vector<value_type> &other)
{
	std::swap(other._alloc, this->_alloc);
	std::swap(other._start, this->_start);
	std::swap(other._end, this->_end);
	std::swap(other._end_capacity, this->_end_capacity);
}
