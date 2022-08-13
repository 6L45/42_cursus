#include "span.hpp"

int main()
{
	srand((unsigned) time(0));
	{
		Span 	sp1(1987, 1);
		Span 	sp2(10000, 1);
		Span	*ptr = new Span(5, 3);
		Span 	sp3(sp2);
		Span 	sp4(3);
		Span	sp5(6);
		Span	sp6(*ptr);

		std::cout << "personnal tests" << std::endl;
		std::cout << std::endl;

		std::cout << "sp1 shortesSpan : " << sp1.shortestSpan() << std::endl;
		std::cout << "sp1 longestSpan : " << sp1.longestSpan() << std::endl;

		std::cout << std::endl;
		std::cout << "sp2 shortesSpan : " << sp2.shortestSpan() << std::endl;
		std::cout << "sp3 shortesSpan : " << sp3.shortestSpan() << std::endl;

		std::cout << std::endl;
		std::cout << "sp2 longestSpan : " << sp2.longestSpan() << std::endl;
		std::cout << "sp3 longestSpan : " << sp3.longestSpan() << std::endl;

		std::cout << std::endl;
		std::cout << std::endl;

		sp5 = *ptr;
		std::cout << "ptr shortesSpan : " << ptr->shortestSpan() << std::endl;
		std::cout << "ptr longestSpan : " << ptr->longestSpan() << std::endl;
		
		std::cout << std::endl;
		delete ptr;

		std::cout << "sp5 shortesSpan : " << sp5.shortestSpan() << std::endl;
		std::cout << "sp6 shortesSpan : " << sp6.shortestSpan() << std::endl;

		std::cout << "sp5 longestSpan : " << sp5.longestSpan() << std::endl;
		std::cout << "sp5 longestSpan : " << sp6.longestSpan() << std::endl;

		std::cout << std::endl;
		try
		{
			sp5.addNumber(99);
		}
		catch (std::exception &e)
		{
			std::cerr << "sp5 : " << e.what() << std::endl;
		}
		try
		{
			sp6.addNumber(99);
		}
		catch (std::exception &e)
		{
			std::cerr << "sp6 : " << e.what() << std::endl;
		}
		try
		{
			for (int i = 0; i < 4 ; ++i)
				sp4.addNumber(i);
		}
		catch (std::exception &e)
		{
			std::cerr << "sp4 : " << e.what() << std::endl;
		}
	}
	{
		std::cout << std::endl;
		std::cout << "given main subject";
		std::cout << std::endl;
		Span sp = Span(5);
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		std::cout << sp.shortestSpan() << std::endl;
		std::cout << sp.longestSpan() << std::endl;
	}

	return (0);
}