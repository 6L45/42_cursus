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
		void	letsSee() const;

		Cat		&operator=(Cat const &);

	private :
		Brain *cerv;
};

class Dog : public Animal
{
	public :
		Dog();
		Dog(Dog const &);
		~Dog();

		void	makeSound() const;
		void	letsSee() const;

		Dog		&operator=(Dog const &);

	private :
		Brain *cerv;
};

#endif
