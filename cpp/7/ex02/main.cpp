#include "array.hpp"
# define MAX_VAL 750

int	main()
{
	{
		Array<int>	*ptr_arr = new Array<int>(14);

		for (unsigned int i = 0; i < ptr_arr->size(); i++)
			(*ptr_arr)[i] = i;
		(*ptr_arr)[3] = 42;

		Array<int>	arr1(*ptr_arr);
		Array<int>	arr2;
		arr2 = arr1;
		ptr_arr->print();
		delete ptr_arr;
		arr1.print();
		arr2.print();	
	}
	std::cout << std::endl;
	{
		Array<float>	*ptr_arr = new Array<float>(14);

		for (unsigned int i = 0; i < ptr_arr->size(); i++)
			(*ptr_arr)[i] = i;
		(*ptr_arr)[3] = 42;

		Array<float>	arr1(*ptr_arr);
		Array<float>	arr2;
		arr2 = arr1;
		ptr_arr->print();
		delete ptr_arr;
		arr1.print();
		arr2.print();	
	}
	std::cout << std::endl;
	{
		Array<double>	*ptr_arr = new Array<double>(14);

		for (unsigned int i = 0; i < ptr_arr->size(); i++)
			(*ptr_arr)[i] = i;
		(*ptr_arr)[3] = 42;

		Array<double>	arr1(*ptr_arr);
		Array<double>	arr2;
		arr2 = arr1;
		ptr_arr->print();
		delete ptr_arr;
		arr1.print();
		arr2.print();	
	}
	std::cout << std::endl;
	{
		Array<std::string>	*ptr_arr = new Array<std::string>(14);

		for (unsigned int i = 0; i < ptr_arr->size(); i++)
			(*ptr_arr)[i] = std::to_string(i);
		(*ptr_arr)[3] = 42;

		Array<std::string>	arr1(*ptr_arr);
		Array<std::string>	arr2;
		arr2 = arr1;
		ptr_arr->print();
		delete ptr_arr;
		arr1.print();
		arr2.print();	
	}

	{
		Array<int> numbers(MAX_VAL);
		int* mirror = new int[MAX_VAL];
		srand(time(NULL));
		for (int i = 0; i < MAX_VAL; i++)
		{
			const int value = rand();
			numbers[i] = value;
			mirror[i] = value;
		}
		//SCOPE
		{
			Array<int> tmp = numbers;
			Array<int> test(tmp);
		}

		for (int i = 0; i < MAX_VAL; i++)
		{
			if (mirror[i] != numbers[i])
			{
				std::cerr << "didn't save the same value!!" << std::endl;
				return 1;
			}
		}
		try
		{
			numbers[-2] = 0;
		}
		catch(const std::exception& e)
	 	{
			std::cerr << e.what() << '\n';
		}
		try
		{
			numbers[MAX_VAL] = 0;
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << '\n';
		}
		for (int i = 0; i < MAX_VAL; i++)
		{
			numbers[i] = rand();
		}
		delete [] mirror;
	}
	return (0);
}
