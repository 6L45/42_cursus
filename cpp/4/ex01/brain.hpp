#ifndef BRAIN_HPP
# define BRAIN_HPP

# include <iostream>
# include <string>

#define out std::cout <<
#define nl << std::endl

class Brain
{
	public :
		Brain();
		Brain(Brain const &);
		~Brain();

		Brain	&operator=(Brain const &);

		std::string ideas[100];
};

#endif
