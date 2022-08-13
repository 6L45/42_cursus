#include "Fixed.hpp"

#define nl << std::endl
#define out std::cout <<

void	subject_main()
{
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );
	
	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;
}

int main(void)
{
	Fixed a;
	Fixed const b(10);
	Fixed const c(42.42f);
	Fixed const d(b);
	Fixed e(12);

	subject_main();

	out std::endl;
	out std::endl;
	out std::endl;

	a = Fixed(1234.4321f);

	a = b;
	out a nl;

	float fl = 10.5;
	a = fl;
	out a nl;

	int in = 9;
	a = in;
	out a nl;

	char ch = 5;
	a = ch;
	out a nl;

	int x = 5;
	int y = 10;
	
	std::cout << Fixed::min( a, b ) << std::endl;

	out std::endl;
	out "----------- additions" nl;
	out x + y + x + x << " xy" nl;
	out a + b + a + a << " ab" nl;
	out a + b + x << " xab" nl;

	out std::endl;
	out "----------- soustraction" nl;
	out "a - b " << a - b - a - a nl;
	out "a - b - y " << a - b - y nl;

	out std::endl;
	out "----------- multiplication" nl;
	out  "a * b " << a * b * a * a nl;
	out "a * b * y " << a * b * y nl;

	out std::endl;
	out "----------- division" nl;
	out "a / b " << a / b / a / a nl;
	out "a / b / y "  << a / b / y nl;

	out std::endl;
	out "----------- +=" nl;
	a += b;
	out "a + b = " << a nl;
	a += y;
	out "a += y " << a nl;
	a += 2.5;
	out "a += 2.5 " << a nl;

	out std::endl;
	out "----------- -=" nl;
	a -= b;
	out "a -= b " << a nl;
	a -= 5.5;
	out "a -= 5.5 " << a nl;

	out a nl;
	out std::endl;
	out "----------- inferieur a" nl;
	if (a < b)
		out "a < b" nl;
	else if (b < a)
		out "b < a" nl;
	if (a < 12.1)
		out "a < 12.1" nl;
	else if (a < 11.99)
		out "a < 11.99" nl;

	out std::endl;
	out "----------- superieur a" nl;
	if (a > b)
		out "a > b" nl;
	else if (b > a)
		out "b > a" nl;
	if (a > 12.1)
		out "a > 12.1" nl;
	else if (a > 11.99)
		out "a > 11.99" nl;

	out std::endl;
	out "----------- inferieur ou egual a" nl;
	if (a <= b)
		out "a <= b" nl;
	else if (b <= a)
		out "b <= a" nl;
	if (a <= 12.0)
		out "a <= 12.0" nl;

	out std::endl;
	out "----------- superieur ou egual a" nl;
	if (a >= 12.1)
		out "a >= 12.1" nl;
	else if (a >= 11.99)
		out "a >= 11.99" nl;
	if (a >= 12.0)
		out "a >= 12.0" nl;

	out std::endl;
	out "----------- egual a" nl;
	if (a == 12.0)
		out "a == 12" nl;
	if (a == 12.1)
		out "a == 12.1 FAIL" nl;
	if (a == e)
		out "a == e" nl;

	out std::endl;
	out "----------- different de" nl;
	if (a != b)
		out "a != b" nl;
	if (a != 13)
		out "a != 13" nl;

	return (0);
}
