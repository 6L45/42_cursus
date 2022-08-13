#include "Karen.hpp"

int main(int argc, char const **argv)
{
	if (argc != 2)
		return (0);

	Karen		karen;
	std::string	alert_lvl(argv[1]);
	size_t		len;

	len = alert_lvl.length();
	for (int i = 0; i < len; i++)
		alert_lvl[i] = std::toupper(alert_lvl[i]);
	karen.complain(alert_lvl);
	return (0);
}