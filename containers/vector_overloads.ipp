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

	if (vecIt == nullptr || cmpIt == nullptr)
	{
		if ((vecIt == nullptr && cmpIt == nullptr) 
			|| (vecIt == nullptr && cmpIt != nullptr))
			return (true);
		else
			return (false);
	}
	else
	{
		while (vecIt != vec.end() && *vecIt == *cmpIt)
		{
			if (cmpIt == cmp.end())
				return (false);
			vecIt++;
			cmpIt++;
		}
		if (*vecIt == *cmpIt && vec.size() != cmp.size())
			return (vec.size() < cmp.size());
		return (*vecIt < *cmpIt);
	}
}

template<class T, class Allocator>
bool	operator<=(const ft::vector<T, Allocator> &vec, const ft::vector<T> &cmp)
{
	typename ft::vector<T, Allocator>::const_iterator vecIt = vec.begin();
	typename ft::vector<T, Allocator>::const_iterator cmpIt = cmp.begin();

	if (vecIt == nullptr || cmpIt == nullptr)
	{
		if ((vecIt == nullptr && cmpIt == nullptr) 
			|| (vecIt == nullptr && cmpIt != nullptr))
			return (true);
		else
			return (false);
	}
	else
	{
		while (vecIt != vec.end() && *vecIt == *cmpIt)
		{
			if (cmpIt == cmp.end())
				return (false);
			vecIt++;
			cmpIt++;
		}
		if (*vecIt == *cmpIt && vec.size() != cmp.size())
			return (vec.size() < cmp.size());
		return (*vecIt <= *cmpIt);
	}
}

template<class T, class Allocator>
bool	operator>(const ft::vector<T, Allocator> &vec, const ft::vector<T> &cmp)
	{ return (!(vec <= cmp)); }

template<class T, class Allocator>
bool	operator>=(const ft::vector<T, Allocator> &vec, const ft::vector<T> &cmp)
	{ return (!(vec < cmp)); }
