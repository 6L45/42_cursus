#include "contact.hpp"

/***************************** CONSTRUCT DESTRUCT *****************************/
/******************************************************************************/
Phonebook::Phonebook()
{
	this->book = new Contact[8];
}

Phonebook::~Phonebook()
{
	delete [] this->book;
}


/******************************* PRIVATE METHOD *******************************/
/******************************************************************************/
void	Phonebook::space_filler(std::string var)
{
	int	offset;

	offset = 10 - var.length();
	while (offset--)
			out << " ";
}

void	Phonebook::print_raw(long i)
{
	out << "|  " << this->book[i].index << "  |";
	space_filler(this->book[i]._firstName);
	out << this->book[i]._firstName << "|";
	space_filler(this->book[i]._lastName);
	out << this->book[i]._lastName << "|";
	space_filler(this->book[i]._nickName);
	out << this->book[i]._nickName << "|";
}

void	Phonebook::slide_contacts()
{
	int	i = 1;
	std::string info[5];
	
	while (i < 8)
	{
		this->book[i].reverse_contact_info(info);
		this->book[i - 1].set_contact_infos(info);
		i++;
	}
	i--;
	this->book[i].set_contact_infos(this->page);
}

void	Phonebook::add_new_contact()
{
	int	i = 0;

	while (i < 8 && this->book[i]._filled)
		i++;
	if (i > 7)
		slide_contacts();
	else
	{
		this->book[i].index = i + 1;
		this->book[i].set_contact_infos(this->page);
	}
}


/******************************** PUBLIC METHOD *******************************/
/******************************************************************************/
void	Phonebook::print_contact(long index)
{
	int	i = 0;
	int	offset;

	out nl;
	out << "|index| FirstName|  LastName|  NickName|" nl;
	out << "|-----|----------|----------|----------|" nl;
	if (index < 0)
	{
		if (i == 0 && book[i]._filled == false)
			out << "|     ABSOLUTLY NO FRIEND AT ALL !     |";
		else
			out << "|            INVALID INDEX !           |";
	}
	else if (index == 0)
	{
		if (i == 0 && book[i]._filled == false)
			out << "|     ABSOLUTLY NO FRIEND AT ALL !     |";
		else
		{
			while (i < 8 && this->book[i].index)
			{
				print_raw(i);
				if (i < 7 && this->book[i + 1].index > 0)
					out nl << "|-----|----------|----------|----------|" nl;
				i++;
			}
		}
		
	}
	else
	{
		if (i == 0 && book[i]._filled == false)
			out << "|     ABSOLUTLY NO FRIEND AT ALL !     |";
		else
		{	
			while (i < 8 && i < index && this->book[i].index)
				i++;
			if (i != index)
				out << "|            INVALID INDEX !           |";
			else
				print_raw(i - 1);
		}
	}
	out nl << "|-----|----------|----------|----------|" nl;
}

int	Phonebook::get_user_info()
{
	static std::string	messages[5] = {
		"Enter first name",
		"Enter last name",
		"Enter nickname",
		"Enter phone number",
		"Enter darkest secret"
	};
	std::string			user_input;

	for (int column = 0; column < 5; column++)
	{
		out << messages[column] nl;
		std::cin >> user_input;
		if (std::cin.eof())
			return (0);
		else if (user_input.length() > 10)
		{
			user_input[9] = '.';
			user_input.resize(10);
		}
		this->page[column] = user_input;
	}
	add_new_contact();
	return (1);
}
