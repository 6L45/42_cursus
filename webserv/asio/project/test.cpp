/*
#ifndef _WIN32
#define _WIN32_WINNT 0x0A00
*/

# define ASIO_STANDALONE
//# define out std::cout
//# define nl std::endl

# include <chrono>
# include <iostream>
# include <boost/asio.hpp>
# include <boost/asio/ts/buffer.hpp>
# include <boost/asio/ts/internet.hpp>
# include <thread>

using namespace boost;

std::vector<char> vBuffer(20 * 1024);

void	grabSomeData(asio::ip::tcp::socket &socket)
{
	socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
	[&](std::error_code ec, std::size_t length)
	{
		if (!ec)
		{
			std::cout << "\n\nRead " << length << " Bytes\n\n";
			for (int i = 0; i < length; i++)
				std::cout << vBuffer[i];

			grabSomeData(socket);
		}
	});
}


int	main()
{
	boost::system::error_code ec;

	asio::io_context context;

	asio::io_context::work idleWork(context);	

	std::thread	thContext = std::thread([&]{ context.run(); });

	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("51.38.81.49", ec), 80);
	asio::ip::tcp::socket socket(context);

	socket.connect(endpoint, ec);


	if (!ec)
	{
		std::cout << "Connected" << std::endl;
	}
	else
	{
		std::cout << "Failed to connect to address :" << std::endl << ec.message() << std::endl;
	}
	if (socket.is_open())
	{
		grabSomeData(socket);

		std::string sRequest = 
			"GET /index.html HTTP/1.1\r\n"
			"HOST: example.com\r\n"
			"Connection: close\r\n\r\n";

		socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);	
	
	}

	std::system("read -p 'Press Enter to continue' var");

	return (0); 
}