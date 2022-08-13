#ifndef CONTACT_HPP
#define CONTACT_HPP

# include "phonebook.hpp"

class Contact
{
	public :

		Contact();
		~Contact();

		int		index;
		void	set_contact_infos(std::string[5]);
		void	reverse_contact_info(std::string (&)[5]);

		std::string		_firstName;
		std::string		_lastName;
		std::string		_nickName;
		std::string		_phoneNumer;
		std::string		_darkSecret;
		bool			_filled;
};

#endif
