#include "iter.hpp"

int	main()
{
	int intR[5] = {0, 1, 2, 3, 4};
	iter(intR, 5, &display); out std::endl;

	float floatR[5] = {0.0f, 1.1f, 2.2f, 3.3f, 4.4f};
	iter(floatR, 5, &display); out std::endl;

	double doubleR[5] = {0.00, 1.11, 2.22, 3.33, 4.44};
	iter(doubleR, 5, &display); out std::endl;

	bool boolR[2] = {false, true};
	iter(boolR, 2, &display); out std::endl;

	std::string stringR[5] = {"phrase 1", "phrase 2", "phrase 3", "phrase 4", "phrase 5"};
	iter(stringR, 5, &display);	out std::endl;
	iter(stringR, 2, &display); out std::endl;
	iter(stringR, 0, &display); out std::endl;
	return (0);
}
