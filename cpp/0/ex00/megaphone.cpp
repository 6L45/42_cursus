#include <iostream>

#define NL << std::endl

int	main(int argc, char **argv)
{
	std::string ret;

	if (argc < 2)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" NL;
	else
	{
		for (int i = 1; i < argc; i++)
		{
			std::string args(argv[i]);

			for (int j = 0; j < args.length(); j++)
				std::cout << (char)std::toupper(args[j]);
			if (i + 1 < argc)
				std::cout << " ";
		}
		std::cout << std::endl;
	}
	return (0);
}