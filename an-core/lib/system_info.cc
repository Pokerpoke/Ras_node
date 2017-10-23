/**
 * Copyright (c) 2017-2018 南京航空航天 航空通信网络研究室
 * 
 * @file
 * @author     姜阳
 * @date       2017.07
 * @brief      用于获取系统的os版本，内存占用，cpu型号等信息。
 * @version    0.0.1
 * @note       使用shell命令获取，可能有些系统无法成功获取。定义输出的数组要足够大。
 * 
 */

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "system_info.h"

namespace an
{
namespace core
{

system_info::system_info()
{
}

/**
 * 使用popen执行命令
 * 
 * @param shell指令
 * @param 输出数组
 * @return 正常结束返回0，管道打开失败返回-1。
 * 
 */
int system_info::popen_to_char(const char *cmd, char *out)
{
	FILE *fp;
	unsigned int index = 0;

	if ((fp = popen(cmd, "r")) == NULL)
	{
		fprintf(stderr, "Pipe open failed.");
		return -1;
	}
	else
	{
		fseek(fp, 0, SEEK_SET);
		while (!feof(fp))
		{
			out[index] = fgetc(fp);
			if (out[index] != '\0')
			{
				index++;
			}
			// TODO:输出数据大小检测，目前需要手动分配足够大的空间。
			// if (index > len)
			// {
			// 	break;
			// }
		}
		out = strtok(out, "\n");
	}

	pclose(fp);

	return 0;
}

/**
 * 使用popen执行命令
 * @param shell指令
 * @param 输出到string
 * @return 正常结束返回0，管道打开失败返回-1。
 */
int system_info::popen_to_string(const char *cmd, std::string &out)
{
	char temp[200];

	popen_to_char(cmd, temp);
	out = temp;

	return 0;
}

/**
 * 使用"uname -sr"获取系统版本
 * @param 输出到char数组
 * @return 正常结束返回0。
 * 
 */
int system_info::os_info(char *out)
{
	const char *cmd = "uname -sr";

	popen_to_char(cmd, out);

	return 0;
}

/**
 * 使用"uname -sr"获取系统版本
 * @param 输出到string
 * @return 正常结束返回0。
 */
int system_info::os_info(std::string &out)
{
	const char *cmd = "uname -sr";

	popen_to_string(cmd, out);

	return 0;
}

/**
 * 使用"free | grep Mem"获取已用内存
 * @param 输出到long
 * @return 正常结束返回0。
 */
int system_info::memory_used(long &out)
{
	const char *cmd = "free | grep Mem";
	char temp[80];

	popen_to_char(cmd, temp);
	strtok(temp, ":");
	strtok(NULL, " ");
	out = atoi(strtok(NULL, " "));

	return 0;
}

/**
 * 使用"free | grep Mem"获取总内存
 * @param 输出到long
 * @return 正常结束返回0。
 */
int system_info::memory_total(long &out)
{
	const char *cmd = "free | grep Mem";
	char temp[80];

	popen_to_char(cmd, temp);
	strtok(temp, ":");
	out = atoi(strtok(NULL, " "));

	return 0;
}

/**
 * 使用"cat /proc/cpuinfo | grep name"获取cpu信息
 * @param 输出到char
 * @return 正常结束返回0。
 */
int system_info::cpu_info(char *out)
{
	const char *cmd = "cat /proc/cpuinfo | grep name";

	popen_to_char(cmd, out);
	strtok(out, ":");
	char *temp = strtok(NULL, "\n");
	strcpy(out, temp);

	return 0;
}

system_info::~system_info()
{
}
}
}
