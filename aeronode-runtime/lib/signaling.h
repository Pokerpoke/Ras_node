/**
 * 
 * Copyright (c) 2018 南京航空航天大学 航空通信网络研究室
 * 
 * @file
 * @author   姜阳 (j824544269@gmail.com)
 * @date     2018-06
 * @brief    
 * @version  0.0.1
 * 
 * Last Modified:  2018-07-03
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#ifndef _SIGNALING_H_
#define _SIGNALING_H_

#include <map>
#include <string>
#include <mutex>
#include <condition_variable>

namespace an
{
namespace core
{
// @TODO: read from file
class Signaling
{
  public:
    Signaling();
    ~Signaling();

    int encoder();
    int decoder();

    std::string get(const std::string &value);
    int get_integer(const std::string &value);
    std::string get_string(const std::string &value);
    bool insert(const std::string &key,
                const std::string &value);
    bool set(const std::string &key,
             const std::string &value);
    bool set(const std::string &key,
             const int &value);
    bool remove(const std::string &key);
    bool enable_heartbeat();

  private:
    std::map<std::string, std::string> signal;
    std::mutex signaling_mutex;
    std::condition_variable signaling_condition;

    // messages
    /// url like requests, such as "/11:8338/voice?rate=8000&coder=g729"
    std::string url;
};
} // namespace core
} // namespace an
#endif //!_SIGNALING_H_