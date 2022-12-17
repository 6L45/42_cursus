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
{
	typename ft::vector<T, Allocator>::const_iterator vecIt = vec.begin();
	typename ft::vector<T, Allocator>::const_iterator cmpIt = cmp.begin();

	while (vecIt != vec.end() - 1)
	{
		if (cmpIt == cmp.end())
			return (false);
		else if (*vecIt != *cmpIt)
			break;
		vecIt++;
		cmpIt++;
	}
	if (*vecIt == *cmpIt && vec.size() != cmp.size())
		return (vec.size() < cmp.size());
	return (*vecIt < *cmpIt);
}

template<class T, class Allocator>
bool	operator<=(const ft::vector<T, Allocator> &vec, const ft::vector<T> &cmp)
{
	typename ft::vector<T, Allocator>::const_iterator vecIt = vec.begin();
	typename ft::vector<T, Allocator>::const_iterator cmpIt = cmp.begin();

	while (vecIt != vec.end() - 1)
	{
		if (cmpIt == cmp.end())
			return (false);
		else if (*vecIt != *cmpIt)
			break;
		vecIt++;
		cmpIt++;
	}
	if (*vecIt == *cmpIt && vec.size() != cmp.size())
		return (vec.size() < cmp.size());
	return (*vecIt <= *cmpIt);
}

template<class T, class Allocator>
bool	operator>(const ft::vector<T, Allocator> &vec, const ft::vector<T> &cmp)
	{ return (!(vec <= cmp)); }

template<class T, class Allocator>
bool	operator>=(const ft::vector<T, Allocator> &vec, const ft::vector<T> &cmp)
	{ return (!(vec < cmp)); }
