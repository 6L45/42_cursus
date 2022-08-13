#include "contact.hpp"

Contact::Contact()
{
	this->index = 0;
	this->_filled = false;
}

Contact::~Contact()
{
	;	
}

void	Contact::reverse_contact_info(std::string (&info)[5])
{
	info[0] = this->_firstName;
	info[1] = this->_lastName;
	info[2] = this->_nickName;
	info[3] = this->_phoneNumer;
	info[4] = this->_darkSecret;
}

void	Contact::set_contact_infos(std::string page[5])
{
	this->_firstName = page[0];
	this->_lastName = page[1];
	this->_nickName = page[2];
	this->_phoneNumer = page[3];
	this->_darkSecret = page[4];
	this->_filled = true;
}
