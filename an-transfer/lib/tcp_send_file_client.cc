#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>

#include "tcp_client.h"
#include "tcp_send_file_client.h"

using namespace an::core;

namespace an
{
namespace transfer
{
namespace tcp
{

send_file::send_file(const char *dest_ip, int dest_port)
	: client(tcp_client(dest_ip, dest_port))
{
}

int send_file::send(const char *file_name)
{
	std::ifstream t(file_name);
	std::string msg((std::istreambuf_iterator<char>(t)),
					std::istreambuf_iterator<char>());

	client.send_data(msg);

	return 0;
}

send_file::~send_file()
{
}
}
}
}