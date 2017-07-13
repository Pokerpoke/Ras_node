#include <iostream>

#include "tcp_server.h"

using namespace an::core;
int main()
{
	tcp_server s(13374);
	char out[4096];
	s.tcp_listen(out);
	std::cout << out;
	getchar();
	return 0;
}