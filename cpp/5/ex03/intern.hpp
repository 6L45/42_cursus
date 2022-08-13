#ifndef INTERN_HPP
# define INTERN_HPP

#include "form.hpp"

class Form;

class Intern
{
	public :
		Intern();
		~Intern() {};

		Form	*makeForm(std::string, std::string);

	private :
		typedef struct s_form
		{
			std::string form;
			Form	*(Intern::*func)(std::string);
		}				t_form;
		
		t_form	type[3];
		Form	*Shrubber(std::string);
		Form	*Robot(std::string);
		Form	*PresidentialPardon(std::string);
};

#endif
