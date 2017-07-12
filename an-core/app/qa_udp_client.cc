#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

int main(int argc, char **argv)
{
	try
	{
		if (argc != 2)
		{
			std::cerr << "Usage: client <host>" << std::endl;
			return 1;
		}
		boost::asio::io_service io_service;
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}
	std::cout << 1 << "\n";
	getchar();
	return 0;
}