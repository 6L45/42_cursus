#include "webserv.hpp"

int main()
{
//	Webserv test(AF_INET, SOCK_STREAM, 0, PORT, INADDR_ANY);
	Webserv test;

	test.launch();
	return 0;
}

