#ifndef WRONGPET_HPP
# define WRONGPET_HPP

# include "animal.hpp"

class wrongCat : public wrongAnimal
{
	public :
		wrongCat();
		~wrongCat();

		void	makeSound() const;
};

#endif
