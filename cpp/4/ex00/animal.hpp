#ifndef ANIMAL_HPP
# define ANIMAL_HPP

# include <iostream>
# include <string>

#define out std::cout <<
#define nl << std::endl

class	Animal
{
	public :
		Animal();
		Animal(Animal const &);
		virtual ~Animal();

		virtual void	makeSound() const;
		std::string		getType() const;

		Animal	&operator=(Animal const &);

	protected :
		std::string type;
};

class	wrongAnimal
{
	public :
		wrongAnimal();
		virtual ~wrongAnimal();

	void	makeSound() const;
	std::string		getType() const;

	protected :
		std::string type;
};


#endif
