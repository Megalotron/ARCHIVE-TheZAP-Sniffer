#pragma once

#include <iostream>
#include <fstream>
#include <string_view>
#include <map>

namespace log {
enum class source {
    sniffer,
    injector
};

inline std::map<source, std::string_view> source_to_file {
    {source::sniffer,  "sniffer.log"},
    {source::injector, "injector.log"}
};
}

namespace tools {
template<typename ...Args>
void logger(const log::source src, Args &&...data)
{
    std::ofstream file;
    file.open(log::source_to_file[src], std::ios::app);

    (std::cout << ... << data);
    std::cout << std::endl;
    (file << ... << data);
    file << std::endl;
}
}