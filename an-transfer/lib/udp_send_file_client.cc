#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <unistd.h>

#include "udp_client.h"
#include "udp_send_file_client.h"

using namespace an::core;

namespace an
{
namespace transfer
{
namespace udp
{

send_file::send_file(const char *dest_ip, int dest_port)
	: client(udp_client(dest_ip, dest_port))
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