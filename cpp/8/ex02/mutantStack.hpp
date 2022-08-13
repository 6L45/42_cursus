#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <stack>
# include <iostream>
# include <string>

template <typename T>
class MutantStack : public std::stack<T>
{
	public:
		MutantStack(void) : std::stack<T>() {};
		MutantStack(const MutantStack<T> &model) : std::stack<T>(model) {};
		~MutantStack()  {};

		MutantStack<T>& operator=(const MutantStack<T> &);

		typedef typename std::stack<T>::container_type::iterator	iterator;
		iterator													begin(void);
		iterator													end(void);
};

# include "mutantStack.ipp"

#endif
