#include <chrono>
#include <sstream>
#include "logger.hpp"

std::string tools::get_time()
{
    auto actual_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string str = std::ctime(&actual_time);
    str.erase(remove_if(str.begin(), str.end(), [](char a) {return a == '\n';}), str.end());
    return str;
}