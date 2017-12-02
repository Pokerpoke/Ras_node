/**
 * 
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-11
 * @brief    用于获取系统的os版本，内存占用，cpu型号等信息。
 * @version  0.0.1
 * @note     使用shell命令获取，可能有些系统无法成功获取。定义输出的数组要足够大。
 * 
 * Last Modified:  2017-12-02
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#ifndef _SYSTEM_INFO_H_
#define _SYSTEM_INFO_H_

namespace an
{
namespace core
{
/**
 * @brief 系统信息
 */
class system_info
{
public:
	system_info();
	~system_info();

	int os_info(char *out);
	int os_info(std::string &out);
	int cpu_info(char *out);
	int memory_used(long &out);
	int memory_total(long &out);

private:
	int popen_to_char(const char *cmd, char *out);
	int popen_to_string(const char *cmd, std::string &out);
};
}
}

#endif // !_SYSTEM_INFO_H_