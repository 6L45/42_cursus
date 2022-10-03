// CONSTRUCT DESTRUCT
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
	if (cp == *this)
		return ;
	this->_start = this->_alloc.allocate(cp.size() + 1);
	this->_end = this->_start + cp.size();
	this->_end_capacity = this->_start + cp.capacity();

	int	i = 0;
	for (typename ft::vector<value_type>::iterator it = cp.begin(); it != cp.end(); ++it)
	{
		this->_alloc.construct(this->_start + i, *it);
		i++;
	}
}

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

template<class value_type, class allocator_type>
ft::vector<value_type, allocator_type>::vector(size_t count)
{
	this->_start = this->_alloc.allocate(count + 1);
	this->_end_capacity = this->_start + count;
	this->_end = this->_end_capacity;
}

template<class value_type, class allocator_type>
template<class inputIt>
ft::vector<value_type, allocator_type>::vector(inputIt first, inputIt last,
	typename std::enable_if<!std::is_integral<inputIt>::value, inputIt>::type*)
{
	size_t	input_size = last - first;

	this->_start = this->_alloc.allocate(input_size + 1);
	this->_end = this->_start + input_size;
	this->_end_capacity = this->_end;

	std::copy(first, last, this->_start);
}

template<class value_type, class allocator_type>
ft::vector<value_type, allocator_type>::~vector()
{
	if (!this->_start)
		return;
	
	for (pointer bgin = this->_start; bgin != this->_end; bgin++)
		this->_alloc.destroy(bgin);
	this->_alloc.deallocate(this->_start, this->capacity());
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

// ELEMENT ACCESS -------------------------------------------------------------
template<class value_type, class allocator_type>
value_type	&ft::vector<value_type, allocator_type>::at(const unsigned int n) const
{
	if (this->size() < n)
		throw std::out_of_range ("");
	else 
		return (*(this->_start + n));
}

template<class value_type, class allocator_type>
value_type	&ft::vector<value_type, allocator_type>::front() const
{
	return (*this->_start);
}

template<class value_type, class allocator_type>
value_type	&ft::vector<value_type, allocator_type>::back() const
{
	return (*(this->_end - 1));
}

// CAPACITY ------------------------------------------------------------------
template<class value_type, class allocator_type>
bool	ft::vector<value_type, allocator_type>::empty() const
{
	if (this->_start == NULL || this->_start == this->_end - 1)
		return (true);
	return (false);
}

template<class value_type, class allocator_type>
typename allocator_type::size_type
	ft::vector<value_type, allocator_type>::size() const
{
	return (this->_end - this->_start);
}

template<class value_type, class allocator_type>
void	ft::vector<value_type, allocator_type>::reserve(size_t n)
{
	if (this->_end_capacity && n <= this->capacity() - 1)
		return ;

	typename allocator_type::size_type 	old_size = this->size();
	pointer	new_start = this->_alloc.allocate(n + 1);

	for (int i = 0; i < old_size; i++)
	{
		this->_alloc.construct(new_start + i, *(this->_start + i));
		this->_alloc.destroy(this->_start + i);
	}
	if (this->_start)
		this->_alloc.deallocate(this->_start, this->capacity());
	this->_start = new_start;
	this->_end = this->_start + old_size + 1;
	this->_end_capacity = this->_start + n;
}

template<class value_type, class allocator_type>
typename allocator_type::size_type
	ft::vector<value_type, allocator_type>::capacity() const
{
	return (this->_end_capacity - this->_start);
}

template<class value_type, class allocator_type>
typename allocator_type::size_type
	ft::vector<value_type, allocator_type>::max_size() const
{
	return (allocator_type().max_size());
}

// MODIFIERS -------------------------------------------------------------------------
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
	typename std::enable_if<!std::is_integral<inputIt>::value, inputIt>::type*)
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
	typename ft::random_access_iterator<value_type>	bginReplace = pos;

	if (!this->capacity())
	{
		this->_start = this->_alloc.allocate(n + 1);

		for (size_t i = 0; i < n; i++, bginReplace++)
			this->_alloc.construct(bginReplace, val);
		
		this->_end = this->_start + n;
		this->_end_capacity = this->_end;
	}
	else if (this->size() + n > this->capacity())
	{
		size_t					offset = pos - this->_start;
		ft::vector<value_type>	tmp(this->capacity());
		
		std::copy(this->begin(), this->end(), tmp.begin());
		this->clear();
		this->_alloc.deallocate(this->_start, this->capacity());

		this->_start = this->_alloc.allocate(tmp.capacity() + n + 1);
		this->_end = this->_start + tmp.size() + n;
		this->_end_capacity = this->_end;
		std::copy(tmp.begin(), tmp.begin() + offset, this->_start);

		size_t	i = 0;
		while(i < n)
		{
			this->_alloc.construct(this->_start + i, val);
			i++;
		}

		std::copy(tmp.begin() + offset, tmp.end(), this->begin + offset + i);
	}
	else
	{
		ft::vector<value_type> tmp(this->capacity() - pos);
		std::copy(pos, this->_end, tmp.begin());

		while (bginReplace != this->_end)
		{
			this->_alloc.destroy(bginReplace);
			bginReplace++;
		}

		bginReplace = pos;
		for (size_t i = 0; i < n; i++, bginReplace++)
			this->_alloc.construct(bginReplace, val);

		std::copy(tmp.begin(), tmp.end(), bginReplace);	
		this->_end += n;
	}
	return (pos);
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

// ITERATOR STUFF -------------------------------------------------------------
template<class value_type, class allocator_type>
typename ft::random_access_iterator<value_type>
	ft::vector<value_type, allocator_type>::begin(void) const
{
	return (this->_start);
}

template<class value_type, class allocator_type>
typename ft::random_access_iterator<value_type>
	ft::vector<value_type, allocator_type>::end(void) const
{
	return (this->_end);
}

// OVERLOADS --------------------------------------------------------------------
template<class value_type, class allocator_type>
bool	ft::vector<value_type, allocator_type>::operator==(const ft::vector<value_type> &cmp) const
{
	if (this->size() != cmp.size())
		return (false);

	for (typename ft::vector<value_type>::iterator thisIt = this->begin(), cmpIt = cmp.begin();
			thisIt != this->end() && cmpIt != cmp.end();
			thisIt++, cmpIt++)
		{
			if (*thisIt != *cmpIt)
				return (false);
		}

		return (true);
}

template<class value_type, class allocator_type>
bool	ft::vector<value_type, allocator_type>::operator!=(const ft::vector<value_type> &cmp) const
{
	return (!(*this == cmp));
}

template<class value_type, class allocator_type>
bool	ft::vector<value_type, allocator_type>::operator<(const ft::vector<value_type> &cmp) const
{
	typename ft::vector<value_type>::iterator thisIt = this->begin();
	typename ft::vector<value_type>::iterator cmpIt = cmp.begin();

	if (thisIt == nullptr || cmpIt == nullptr)
	{
		if (thisIt == nullptr && cmpIt != nullptr)
			return (true);
		else
			return (false);
	}
	else
	{
		while (thisIt != this->end() && cmpIt != cmp.end() && *thisIt == *cmpIt)
		{
			thisIt++;
			cmpIt++;
		}
		return (*thisIt < *cmpIt);
	}
}

template<class value_type, class allocator_type>
bool	ft::vector<value_type, allocator_type>::operator<=(const ft::vector<value_type> &cmp) const
{
	typename ft::vector<value_type>::iterator thisIt = this->begin();
	typename ft::vector<value_type>::iterator cmpIt = cmp.begin();

	if (thisIt == nullptr || cmpIt == nullptr)
	{
		if ((thisIt == nullptr && cmpIt != nullptr) 
			|| (thisIt == nullptr && cmpIt == nullptr))
			return (true);
		else
			return (false);
	}
	else
	{
		while (thisIt != this->end() && cmpIt != cmp.end() && *thisIt == *cmpIt)
		{
			thisIt++;
			cmpIt++;
		}
		return (*thisIt <= *cmpIt);
	}
	
}


template<class value_type, class allocator_type>
bool	ft::vector<value_type, allocator_type>::operator>(const ft::vector<value_type> &cmp) const
{
	return (!(*this <= cmp));
}


template<class value_type, class allocator_type>
bool	ft::vector<value_type, allocator_type>::operator>=(const ft::vector<value_type> &cmp) const
{
	return (!(*this < cmp));
}
