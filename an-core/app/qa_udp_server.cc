// #include <iostream>

// #include "udp_server.h"

// int main()
// {
// 	const char *listen_ip = "127.0.0.1";
// 	const char *listen_port = "13374";

// 	udp_server s(listen_ip, listen_port);

// 	s.listen()

// 	std::cout << 1;
// 	getchar();
// 	return 0;
// }

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::udp;

std::string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}

int main()
{
	try
	{
		boost::asio::io_service io_service;

		udp::socket socket(io_service, udp::endpoint(udp::v4(), 13));

		for (;;)
		{
			boost::array<char, 1> recv_buf;
			udp::endpoint remote_endpoint;
			boost::system::error_code error;
			socket.receive_from(boost::asio::buffer(recv_buf),
								remote_endpoint, 0, error);

			if (error && error != boost::asio::error::message_size)
				throw boost::system::system_error(error);

			std::string message = make_daytime_string();

			boost::system::error_code ignored_error;
			socket.send_to(boost::asio::buffer(message),
						   remote_endpoint, 0, ignored_error);
		}
	}
	catch (std::exception &e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}