
template<class value_type, class allocator_type>
ft::Vector<value_type, allocator_type>::Vector(const allocator_type &alloc)
{
	this->_alloc = alloc;
	this->_start = NULL;
	this->_end = NULL;
	this->_end_capacity = NULL;
}

template<class value_type, class allocator_type>
typename allocator_type::size_type
	ft::Vector<value_type, allocator_type>::size()
{
	return (this->_end - this->_start);
}

template<class value_type, class allocator_type>
typename allocator_type::size_type
	ft::Vector<value_type, allocator_type>::max_capacity()
{
	return (this->_end_capacity - this->_start);
}

template<class value_type, class allocator_type>
void	ft::Vector<value_type, allocator_type>::push_back(value_type val)
{
	if (!this->_start)
	{
		this->_start = this->_alloc.allocate(1);
		this->_alloc.construct(this->_start, val);
		this->_end = this->_start + 1;
		this->_end_capacity = this->_end;
	}
	else if (this->_end == this->_end_capacity)
	{
		typename allocator_type::size_type	old_size = this->size();
		pointer new_start = this->_alloc.allocate(old_size * 2);
		
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
/*
		for (int i = 0; i < this->size() ; i++)
			out *(this->_start + i) << " ";
		out nl;
*/	}
	else
	{
		this->_alloc.construct(this->_start + this->size(), val);
		this->_end++;
	}

		for (int i = 0; i < this->size() ; i++)
			out *(this->_start + i) << " ";
		out nl;
}

