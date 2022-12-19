
template<class value_type, class container_type>
ft::stack<value_type, container_type>::stack(const container_type &ctn)
	{ this->stk = ctn; }

template<class value_type, class container_type>
bool	ft::stack<value_type, container_type>::empty(void) const
	{ return (this->stk.empty()); }

template<class value_type, class container_type>
size_t	ft::stack<value_type, container_type>::size(void) const
	{ return (this->stk.size()); }

template<class value_type, class container_type>
void	ft::stack<value_type, container_type>::push(const value_type &val)
	{ this->stk.push_back(val); }

template<class value_type, class container_type>
void	ft::stack<value_type, container_type>::pop(void)
	{ this->stk.pop_back(); }

template<class value_type, class container_type>
value_type	&ft::stack<value_type, container_type>::top(void)
	{ return (this->stk.back()); }
