#ifndef MATERIA_HPP
# define MATERIA_HPP

#include <iostream>
#include <string>

# include "character.hpp"

class ICharacter;

class AMateria
{
	public :
		//construct
		AMateria(std::string const &type) : nature_type(type) {};
		virtual ~AMateria(){};

		//var
		std::string const	nature_type;
		
		//methods
		std::string const	&getType() const;
		virtual AMateria	*clone() const = 0;
		virtual void		use(ICharacter &target) {};
};

class IMateriaSource
{
	public:
		virtual ~IMateriaSource() {}
		virtual void learnMateria(AMateria*) = 0;
		virtual AMateria* createMateria(std::string const & type) = 0;
};


class Ice : public AMateria
{
	public :
		//construct
		Ice() : AMateria("ice") {};
		~Ice();

		AMateria	*clone() const;
		void		use(ICharacter &target);
};

class Cure : public AMateria
{
	public :
		//construct
		Cure() : AMateria("cure") {};
		~Cure();

		AMateria	*clone() const;
		void		use(ICharacter &target);
};

#endif
