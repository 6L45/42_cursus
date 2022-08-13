#ifndef GOODPET_HPP
# define GOODPET_HPP

# include "animal.hpp"

class Cat : public Animal
{
	public :
		Cat();
		Cat(Cat const &);
		~Cat();

		void	makeSound() const;
		Cat		&operator=(Cat const &);
};

class Dog : public Animal
{
	public :
		Dog();
		Dog(Dog const &);
		~Dog();

		void	makeSound() const;
		Dog		&operator=(Dog const &);
};

#endif
