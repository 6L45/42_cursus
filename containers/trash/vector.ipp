// CONSTRUCT DESTRUCT

template<class value_type, class allocator_type>
ft::Vector<value_type, allocator_type>::Vector(const allocator_type &alloc)
{
	this->_alloc = alloc;
	this->_start = NULL;
	this->_end = NULL;
	this->_end_capacity = NULL;
}

template<class value_type, class allocator_type>
ft::Vector<value_type, allocator_type>::~Vector()
{
	if (!this->_start)
		return ;

	pointer	it = this->_start;
	for (pointer it = this->_start; it != this->_end; it++)
		this->_alloc.destroy(it);
	this->_alloc.deallocate(this->_start, this->capacity());
}

template<class value_type, class allocator_type>
ft::Vector<value_type, allocator_type>::Vector(std::initializer_list<value_type> lst)
{
	for (typename std::initializer_list<value_type>::iterator it = lst.begin();
			it != lst.end(); it++)
		this->push_back(*it);
}

// ELEMENT ACCESS -------------------------------------------------------------
template<class value_type, class allocator_type>
value_type	ft::Vector<value_type, allocator_type>::at(unsigned int n)
{
	if (this->size() < n)
	{
		out "NONONO Vector::at()" << std::endl;
		exit(1); // TO DO throw;
	}
	else 
		return (*(this->_start + n));
}

template<class value_type, class allocator_type>
value_type	&ft::Vector<value_type, allocator_type>::front()
{
	return (*this->_start);
}

template<class value_type, class allocator_type>
value_type	&ft::Vector<value_type, allocator_type>::back()
{
	return (*(this->_end - 1));
}


// CAPACITY ------------------------------------------------------------------
template<class value_type, class allocator_type>
bool	ft::Vector<value_type, allocator_type>::empty()
{
	if (this->_start == NULL || this->_start == this->_end - 1)
		return (true);
	return (false);
}

template<class value_type, class allocator_type>
typename allocator_type::size_type
	ft::Vector<value_type, allocator_type>::size()
{
	return (this->_end - this->_start);
}

template<class value_type, class allocator_type>
void	ft::Vector<value_type, allocator_type>::reserve(size_t n)
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
	ft::Vector<value_type, allocator_type>::capacity()
{
	return (this->_end_capacity - this->_start);
}


// MODIFIERS -------------------------------------------------------------------------
template<class value_type, class allocator_type>
void	ft::Vector<value_type, allocator_type>::push_back(value_type val)
{
	if (!this->_start)
	{
		this->_start = this->_alloc.allocate(2);
		this->_alloc.construct(this->_start, val);
		this->_end = this->_start + 1;
		this->_end_capacity = this->_end;
	}
	else if (this->_end > this->_end_capacity)
	{
		typename allocator_type::size_type	old_size = this->size();
		pointer new_start = this->_alloc.allocate((old_size * 2) + 1);
		
		for (int i = 0; i < old_size; i++)
		{
			this->_alloc.construct(new_start + i, *(this->_start + i));
			this->_alloc.destroy(this->_start + i);
		}
		this->_alloc.deallocate(this->_start, this->size());
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
void	ft::Vector<value_type, allocator_type>::clear()
{
	if (!this->_start)
		return ;
	
	for (pointer it = this->_start; it != this->_end; it++)
		this->_alloc.destroy(it);
	this->_end = this->_start;
}

template<class value_type, class allocator_type>
void	ft::Vector<value_type, allocator_type>::swap(ft::Vector<value_type> &other)
{
	std::swap(other._alloc, this->_alloc);
	std::swap(other._start, this->_start);
	std::swap(other._end, this->_end);
	std::swap(other._end_capacity, this->_end_capacity);
}

// ITERATOR STUFF -------------------------------------------------------------
template<class value_type, class allocator_type>
typename ft::random_access_iterator<value_type>
	ft::Vector<value_type, allocator_type>::begin(void)
{
	return (this->_start);
}

template<class value_type, class allocator_type>
typename ft::random_access_iterator<value_type>
	ft::Vector<value_type, allocator_type>::end(void)
{
	return (this->_end);
}
