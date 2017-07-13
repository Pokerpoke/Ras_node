#ifndef _TCP_SERVER_H_
#define _TCP_SERVER_H_

#include <netinet/in.h>
#include <sys/socket.h>

namespace an
{
namespace core
{
class tcp_server
{
  public:
	tcp_server(int server_port);
	~tcp_server();
	int tcp_listen(char *out);

  private:
	int tcp_server_init(int server_port);
	int listen_socket, conn_socket;
	struct sockaddr_in server_addr;
};
}
}

#endif