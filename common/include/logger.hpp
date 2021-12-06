#pragma once

#include <iostream>
#include <fstream>
#include <map>
#include "color.hpp"

namespace tools {

enum class log {
    sniffer,
    injector
};

std::string get_time();

template<typename ...Args>
void logger(const log src, Args &&...data)
{
    static const std::map<log, std::string> log_to_string {
        {log::sniffer,  "sniffer"},
        {log::injector, "injector"}
    };

    std::ofstream file;
    file.open(log_to_string.at(src) + ".log", std::ios::app);

    std::cout << color::yellow << '[' << get_time() << "] " << color::reset;
    std::cout << color::cyan << '[' << log_to_string.at(src) << "] " << color::reset;
    ((std::cout << data << ' '), ...) << std::endl;

    file << '[' << get_time() << "] ";
    ((file << data << ' '), ...) << std::endl;
}
}