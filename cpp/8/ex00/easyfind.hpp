#ifndef EASYFIND_HPP
#define EASYFIND_HPP

# include <iostream>
# include <vector>
# include <algorithm>

template<typename T>
int	&easyfind(T &container, int n)
{
	typename T::iterator iter = std::find(container.begin(), container.end(), n);
	if (iter == container.end())
		throw std::runtime_error("Not found!");

	return (*iter);
}

#endif
