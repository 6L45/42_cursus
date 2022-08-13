#include "zombie.hpp"

std::string	name_generator(std::string name)
{
	std::string surname[8] = {
		" El ",
		" Le seul et L'unique ",
		" Regular ",
		" Ghoul ",
		" Lich ",
		" Le Magnifique ",
		" El Magnifico ",
		" Mc "
	};

	std::string	letters = "abcdefghijklmnopqrstuvwxyz";
	std::string title;
	std::string full_name;
	int	name_size;

	name_size = (rand() % 6) + 3;

	for (int i = 0; i < name_size; i++)
		title += letters.at(rand() % 26);
	full_name = name + surname[rand() % 8] + title;

	return (full_name);
}

Zombie* zombieHorde(int N, std::string name)
{
	Zombie *horde;
	std::string first_name;

	horde = new Zombie[N];
	for (int i = 0; i < N; i++)
		horde[i].assign_name(name_generator(name));
	return (horde);
}