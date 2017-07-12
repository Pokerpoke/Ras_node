#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "udp_client.h"

using boost::asio::ip::udp;

namespace an
{
namespace core
{

boost::asio::io_service io_service;
udp::socket socket(io_service);
udp::endpoint endpoint;

udp_client::udp_client(const void *t_dest_ip, const void *t_dest_port)
{
	const char *dest_ip = (const char *)t_dest_ip;
	const char *dest_port = (const char *)t_dest_port;

	udp::resolver resolver(io_service);
	udp::resolver::query query(udp::v4(), dest_ip, dest_port);
	endpoint = *resolver.resolve(query);
	socket.open(udp::v4());
}

int udp_client::send(const void *t_msg)
{
	const std::string *msg = (const std::string *)t_msg;
	socket.send_to(boost::asio::buffer(msg, sizeof(msg) - 1), endpoint);
}

udp_client::~udp_client()
{
	socket.close();
}
}
}
