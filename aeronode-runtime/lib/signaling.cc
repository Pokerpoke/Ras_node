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
 * Last Modified:  2018-06-30
 * Modified By:    姜阳 (j824544269@gmail.com)
 * 
 */
#include "signaling.h"
#include <cstdlib>

namespace an
{
namespace core
{
Signaling::Signaling()
{
}

std::string Signaling::get(const std::string &value)
{
    std::unique_lock<std::mutex> lock(signaling_mutex);
    return signal[value];
}

std::string Signaling::get_string(const std::string &value)
{
    std::unique_lock<std::mutex> lock(signaling_mutex);
    return signal[value];
}

int Signaling::get_integer(const std::string &value)
{
    std::unique_lock<std::mutex> lock(signaling_mutex);
    return atoi(signal[value].c_str());
}

bool Signaling::insert(const std::string &key,
                       const std::string &value)
{
    std::unique_lock<std::mutex> lock(signaling_mutex);
    using namespace std;
    return signal.insert(pair<string, string>(key, value)).second;
}

bool Signaling::set(const std::string &key,
                    const std::string &value)
{
    std::unique_lock<std::mutex> lock(signaling_mutex);
    signal[key] = value;
    return signal[key] == value ? true : false;
}

bool Signaling::set(const std::string &key,
                    const int &value)
{
    std::unique_lock<std::mutex> lock(signaling_mutex);
    signal[key] = std::to_string(value);
    return signal[key] == std::to_string(value) ? true : false;
}

bool Signaling::remove(const std::string &key)
{
    std::unique_lock<std::mutex> lock(signaling_mutex);
    return signal.erase(key);
}

Signaling::~Signaling()
{
}
} // namespace core
} // namespace an