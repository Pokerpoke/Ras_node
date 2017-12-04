#ifndef _UDP_SEND_FILE_CLIENT_H_
#define _UDP_SEND_FILE_CLIENT_H_

#include <fstream>
#include "udp_client.h"

namespace an
{
namespace transfer
{
namespace udp
{

class send_file
{
public:
	send_file(const char *dest_ip, int dest_port);
	~send_file();

	int send(const char *file_name);

private:
	an::core::udp_client client;
};
}
}
}

#endif // !_UDP_SEND_FILE_CLIENT_H_