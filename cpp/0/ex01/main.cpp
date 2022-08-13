#include "phonebook.hpp"

static void	title(void)
{
	out << std::endl;
	out << "██████╗ ██╗  ██╗ ██████╗ ███╗   ██╗███████╗██████╗  ██████╗  ██████╗ ██╗  ██╗" nl;
	out << "██╔══██╗██║  ██║██╔═══██╗████╗  ██║██╔════╝██╔══██╗██╔═══██╗██╔═══██╗██║ ██╔╝" nl;
	out << "██████╔╝███████║██║   ██║██╔██╗ ██║█████╗  ██████╔╝██║   ██║██║   ██║█████╔╝ " nl;
	out << "██╔═══╝ ██╔══██║██║   ██║██║╚██╗██║██╔══╝  ██╔══██╗██║   ██║██║   ██║██╔═██╗ " nl;
	out << "██║     ██║  ██║╚██████╔╝██║ ╚████║███████╗██████╔╝╚██████╔╝╚██████╔╝██║  ██╗" nl;
	out << "╚═╝     ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝╚═════╝  ╚═════╝  ╚═════╝ ╚═╝  ╚═╝" nl;
	out nl;
	out << "Welcome to your phonebook !\nThe available entries are : " nl;
	out << " - ADD - SEARCH - EXIT - INDEX CONTACT" nl nl;
}

bool isNumber(std::string str)
{
	int	i = 0;

	if (str[i] == '-' | str[i] == '+')
		i++;
    while (str[i])
    {
        if (!std::isdigit(str[i]))
        	return false;
    	i++;
    }
    return true;
}

bool	dont_push_granny(std::string entry)
{
	if (entry.length() >= 10)
		return (false);
	return (true);
}

int	main(void)
{
	Phonebook	phoneBook;
	int			len;
	std::string	user_input;

	title();
	while (1)
	{
		std::cin >> user_input;
		
		for (int i = 0; i < user_input.length(); i++)
			user_input[i] = std::toupper(user_input[i]);

		if (user_input == "EXIT" || std::cin.eof())
			break ;
		else if (user_input == "ADD")
		{
			out nl;
			if (!phoneBook.get_user_info())
				break ;
			out nl;
			out << "new entry created" nl;
			out << "-----------------" nl;
		}
		else if (user_input == "SEARCH")
		{
			user_input.clear();
			out nl << "enter index contact (0 print all contacts)" nl;
			std::cin >> user_input;
			if (std::cin.eof())
				break ;
			if (isNumber(user_input))
			{
				if (dont_push_granny(user_input))
				{
					long	index = std::stol(user_input);
					phoneBook.print_contact(index);
				}
				else
					out << "Only 8 contacts available\nDon t pretend you have thousands of friends..." nl;
			}
			else
				out << "not a number" nl;
		}

		out nl;
		out << "enter a command" nl;
		user_input.clear();
	}
	return (0);
}
