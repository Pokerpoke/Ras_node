#include <fstream>
#include <iostream>
#include <string>
#include <streambuf>
#include <unistd.h>
#include <vector>

#include "tcp_send_file_client.h"

using namespace an::transfer::tcp;

int main()
{
	const char *dest_ip = "127.0.0.1";
	int dest_port = 13374;

	// const char *file_name = "./an-transfer/example/test.txt";
	const char *file_name = "test.txt";

	send_file s(dest_ip, dest_port);

	s.send(file_name);

	getchar();
	return 0;
}