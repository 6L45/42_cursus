// CONSTRUCT DESTRUCT
template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::map<key_type, mapped_type, key_compare, allocator_type>::map(const key_compare &comp,
																const allocator_type &alloc)
{
	this->_alloc = alloc;
	this->_comp = comp;
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::map<key_type, mapped_type, key_compare, allocator_type>::map(const ft::map<key_type, mapped_type> &cp)
{
	this->_alloc = cp._alloc;
	this->_comp = cp._comp;

//	this->insert(cp.begin(), cp.end());
}


template<class key_type, class mapped_type, class key_compare, class allocator_type>
template<class inputIt>
ft::map<key_type, mapped_type, key_compare, allocator_type>::map(inputIt first, inputIt last,
																const key_compare &comp,
																const allocator_type &alloc,
																typename ft::enable_if<!ft::is_integral<inputIt>::value, inputIt>::type *)
{
//	this->insert(first, last);
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::map<key_type, mapped_type, key_compare, allocator_type>
	ft::map<key_type, mapped_type, key_compare, allocator_type>::operator=
												(const ft::map<key_type, mapped_type> &cpy)
{
/*	if (&cpy == this)
		return (*this);
	this->clear();
	this->insert(cpy.begin(), cpy.end());
	
	return (*this);*/
}

template<class key_type, class mapped_type, class key_compare, class allocator_type>
ft::map<key_type, mapped_type, key_compare, allocator_type>::~map()
{
//	this->clear();
}

