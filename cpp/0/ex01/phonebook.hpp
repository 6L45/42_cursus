#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

# include <iostream>
# include "contact.hpp"

# define nl << std::endl
# define out std::cout

class Contact;

class Phonebook
{
	public :

		Phonebook();
		~Phonebook();

		int		get_user_info();
		void	print_contact(long = -1);

	private :

		std::string	page[5];
	 	Contact	*book;

	 	void	add_new_contact();
	 	void	slide_contacts();
	 	void	print_raw(long);
	 	void	space_filler(std::string var);
};

#endif
