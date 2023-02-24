template<class T, class Allocator>
bool	operator==(const ft::vector<T, Allocator> &vec, const ft::vector<T, Allocator> &cmp)
{
	if (vec.size() != cmp.size())
		return (false);

	for (typename ft::vector<T, Allocator>::const_iterator vecIt = vec.begin(), cmpIt = cmp.begin();
		vecIt != vec.end() && cmpIt != cmp.end();
		vecIt++, cmpIt++)
	{
		if (*vecIt != *cmpIt)
			return (false);
	}
	return (true);
}

template<class T, class Allocator>
bool	operator!=(const ft::vector<T, Allocator> &vec, const ft::vector<T> &cmp)
	{ return (!(vec == cmp)); }

template <class T, class Allocator>
bool	operator<(const ft::vector<T, Allocator> &vec, const ft::vector<T> &cmp)
	{ return ft::lexicographical_compare(vec.begin(), vec.end(), cmp.begin(), cmp.end()); }

template<class T, class Allocator>
bool	operator<=(const ft::vector<T, Allocator> &vec, const ft::vector<T> &cmp)
	{ return (vec < cmp || ft::equal(vec.begin(), vec.end(), cmp.begin())); }

template<class T, class Allocator>
bool	operator>(const ft::vector<T, Allocator> &vec, const ft::vector<T> &cmp) 
	{ return (!(vec <= cmp)); }

template<class T, class Allocator>
bool	operator>=(const ft::vector<T, Allocator> &vec, const ft::vector<T> &cmp)
	{ return (!(vec < cmp)); }
