#include "net_common.hpp"


std::vector<char> vBuffer(20 * 1024);

// recursive read at buffer size ^
// and display
void	grabSomeData(asio::ip::tcp::socket &socket)
{
	// read first param at buffer sizer and apply lambda function
	
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
//	INITIALISATION--------------------------------------------------------------------------------------------------------------------------------------------	

	boost::system::error_code ec;	// get specifique ettor -> erro handler intern to the framwork

	// ASIO need space to perform "stuff" (do its work ?) "it does it with behind the object called asio::iocontext"
	asio::io_context context;	// that's the context that hides all of the platform requierements

	// ASYN PART ------------------------------------------------------------------
		// idlework = do something so you don't stopœ
		asio::io_context::work idleWork(context);
		// asynchronous, read as soon as receive data and wait in the meantime
		// so here your own thread so you don't disturb main process (basically)
		std::thread	thContext = std::thread([&]{ context.run(); });
	//-----------------------------------------------------------------------------

	// address we wanna connect to -> endpoint		param1-make_adresse = transform format - 80=port
	asio::ip::tcp::endpoint endpoint(asio::ip::make_address("51.38.81.49", ec), 80);
	
	// create a socket, the context deliver the implementation
	asio::ip::tcp::socket socket(context);																				// TO DO : Explorer le contexte exacte de l'implémentation pour manipulation des sockets

	socket.connect(endpoint, ec); // connect to endpoint + ec = error handler to know what's wrong (just in case.)
	// PS : can compile without ec.

//	----------------------------------------------------------------------------------------------------------------------------------------------------------	



	if (!ec)
		std::cout << "Connected" << std::endl;
	else
		std::cout << "Failed to connect to address :" << std::endl << ec.message() << std::endl;

	if (socket.is_open())
	{
		// ASYNC on his own thread waiting to read. So declare first 
		grabSomeData(socket);

		// Simple GET http request
		std::string sRequest = 
			"GET /index.html HTTP/1.1\r\n"
			"HOST: example.com\r\n"
			"Connection: close\r\n\r\n";

		// write to socket sRequest = send request		
		socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);												// TO DO : chercher plus de details sur send reveive via socket
	
	}

	std::system("read -p 'Press Enter to continue' var");

	return (0); 
}