#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>
# include "brain.hpp"

class	AAnimal
{
	public :
		AAnimal();
		virtual 		~AAnimal();
		virtual void	makeSound() const = 0;
		std::string		getType() const;

	protected :
		std::string type;
};

#endif
