#ifndef _SYSTEM_INFO_H_
#define _SYSTEM_INFO_H_

#include "system_info.h"

namespace an
{
namespace core
{
class system_info 
{
public:
	system_info();
	~system_info();

	int os_info(char *sys_info);
	int memory_used(long &out);
	int memory_total(long &out);

private:
	int popen_to_char(const char *cmd, char *out);
};
}
}

#endif // !_SYSTEM_INFO_H_