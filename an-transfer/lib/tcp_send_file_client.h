#ifndef _TCP_SEND_FILE_CLIENT_H_
#define _TCP_SEND_FILE_CLIENT_H_

#include <fstream>
#include "tcp_client.h"

namespace an
{
namespace transfer
{
namespace tcp
{

class send_file
{
public:
	send_file(const char *dest_ip, int dest_port);
	~send_file();

	int send(const char *file_name);

private:
	an::core::tcp_client client;
};
}
}
}

#endif // !_TCP_SEND_FILE_CLIENT_H_