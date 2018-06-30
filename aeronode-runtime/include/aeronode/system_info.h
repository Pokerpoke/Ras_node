/**
 * 
 * Copyright (c) 2017 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2017-07
 * @brief    用于获取系统的os版本，内存占用，cpu型号等信息。
 * @version  0.0.2
 * @note     使用shell命令获取，可能有些系统无法成功获取。定义输出的数组要足够大。
 * 
 * Last Modified:  2017-12-11
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#ifndef _SYSTEM_INFO_H_
#define _SYSTEM_INFO_H_

#include <string>
#include <map>
#include <sys/utsname.h>
#include <sys/sysinfo.h>

namespace an
{
namespace core
{
/**
 * @brief 系统信息
 */
class SystemInfo
{
  public:
    SystemInfo();
    ~SystemInfo();

    int update();
    /// 系统信息结构体，包含
    /// - 系统名 sysname (如Linux)
    /// - 网络名 nodename (如ubunut)
    /// - 发行版本 release (如4.13)
    /// - 版本 version (如#20-Ubuntu SMP Mon Nov 6 10:04:08 UTC 2017)
    /// - 硬件标识符 machine (如x86_64)
    ///
    /// @code
    /// 	struct utsname
    /// 	{
    /// 		char sysname[];  /* Operating system name (e.g., "Linux") */
    /// 		char nodename[]; /* Name within "some implementation-defined   network" */
    /// 		char release[];  /* Operating system release (e.g., "2.6.28") */
    /// 		char version[];  /* Operating system version */
    /// 		char machine[];  /* Hardware identifier */
    /// #ifdef _GNU_SOURCE
    /// 		char domainname[]; /* NIS or YP domain name */
    /// #endif
    /// 	};
    /// @endcode
    struct utsname os_info;
    /// 内存信息结构体
    /// @code
    /// struct sysinfo
    /// {
    /// 	long uptime;			 /* Seconds since boot */
    /// 	unsigned long loads[3];  /* 1, 5, and 15 minute load averages */
    /// 	unsigned long totalram;  /* Total usable main memory size */
    /// 	unsigned long freeram;   /* Available memory size */
    /// 	unsigned long sharedram; /* Amount of shared memory */
    /// 	unsigned long bufferram; /* Memory used by buffers */
    /// 	unsigned long totalswap; /* Total swap space size */
    /// 	unsigned long freeswap;  /* Swap space still available */
    /// 	unsigned short procs;	/* Number of current processes */
    /// 	char _f[22];			 /* Pads structure to 64 bytes */
    /// };
    /// @endcode
    struct sysinfo mem_info;
    std::map<std::string, std::string> ip_info;
    // struct _ip_info
    // {
    // 	std::string interface;
    // 	std::string ip;
    // };
    // struct _ip_info ip_info;

  private:
    int _err;

    int get_ip_info();
    int get_os_info();
    int get_mem_info();
};
} // namespace core
} // namespace an

#endif // !_SYSTEM_INFO_H_