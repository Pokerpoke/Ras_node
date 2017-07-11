#include <iostream>
#include <string>
#include <stdio.h>

#include "system_info.h"

using namespace an::core;

int main()
{
	char sys_info[80] = "";
	system_info s;

	s.os_info(sys_info);

	std::cout << sys_info << std::endl;

	long mem_used, mem_total;

	s.memory_used(mem_used);
	std::cout << mem_used << "\n";

	s.memory_total(mem_total);
	std::cout << mem_total << "\n";

	printf("%.2lf%\n", ((double)mem_used / (double)mem_total * 100));

	getchar();

	return 0;
}