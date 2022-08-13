#ifndef ITER_HPP
# define ITER_HPP


# include <iostream>
# include <string>

# define out std::cout <<
# define nl << std::endl

template<typename T>
void	iter(T *tab, unsigned int size, void (*f)(T const &arg))
{
	for (unsigned int i = 0; i < size; i++)
		(*f)(tab[i]);
}

template<typename T>
void	display(T const &arg)
{
	out '[' << arg << ']' << " ";
}

#endif
