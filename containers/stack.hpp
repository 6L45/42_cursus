#ifndef STACK_HPP
# define STACK_HPP

# include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T>>
	class stack
	{
		public :
			typedef T										value_type;
			typedef Container								container_type;
			typedef typename Container::size_type			size_type;
			typedef typename Container::reference			reference;
			typedef typename Container::const_reference		const_reference;
			
			stack(const Container &ctn = Container());
			~stack() {};

			bool			empty(void) const;
			size_t			size(void) const;
			value_type		&top();
			void			push(const value_type &val);
			void			pop();

			friend bool			operator==(const ft::stack<value_type, container_type> &stk,
											const ft::stack<value_type, container_type> &cmp)
				{ return (stk.stk == cmp.stk); }
			friend bool			operator!=(const ft::stack<value_type, container_type> &stk,
											const ft::stack<value_type, container_type> &cmp)
				{ return(stk.stk != cmp.stk); }
			friend bool			operator<(const ft::stack<value_type, container_type> &stk,
											const ft::stack<value_type, container_type> &cmp)
				{ return(stk.stk < cmp.stk); }
			friend bool			operator<=(const ft::stack<value_type, container_type> &stk,
											const ft::stack<value_type, container_type> &cmp)
				{ return(stk.stk <= cmp.stk); }
			friend bool			operator>(const ft::stack<value_type, container_type> &stk,
											const ft::stack<value_type, container_type> &cmp)
				{ return(stk.stk > cmp.stk); }
			friend bool			operator>=(const ft::stack<value_type, container_type> &stk,
											const ft::stack<value_type, container_type> &cmp)
				{ return(stk.stk >= cmp.stk); }
		private :
			Container	stk;

	}; // class stack

} // namespace ft

# include"stack.ipp"

#endif

