#include <iostream>
#include <string>
#include <stdio.h>

#include "logger.h"
#include "system_info.h"

using namespace an::core;

int main()
{
	// logger_init();
	logger_init("./log/test.log");

	char sys_info[80] = "";
	std::string sys_info2;
	system_info s;

	s.os_info(sys_info2);

	std::cout << sys_info2 << std::endl;
	LOG(WARN) << "test";

	long mem_used, mem_total;

	s.memory_used(mem_used);
	std::cout << mem_used << "\n";

	s.memory_total(mem_total);
	std::cout << mem_total << "\n";

	printf("%.2lf%%\n", ((double)mem_used / (double)mem_total * 100));

	char cpu0_info[200] = "";
	s.cpu_info(cpu0_info);
	std::cout << cpu0_info << "\n";

	getchar();

	return 0;
}