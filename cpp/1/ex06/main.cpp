#include "Karen.hpp"

int main(int argc, char const **argv)
{
	if (argc < 2)
	{
		std::cout << "Probably complaining about insignificant problems" << std::endl;
		return (0);
	}

	Karen		karen;
	std::string	alert_lvl(argv[1]);
	size_t		len;

	len = alert_lvl.length();
	for (int i = 0; i < len; i++)
		alert_lvl[i] = std::toupper(alert_lvl[i]);
	if (argc > 2)
		karen.complain("whtever");
	else
		karen.complain(alert_lvl);
	return 0;
}