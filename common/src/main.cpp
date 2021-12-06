#include <iostream>
#include "sniffer.hpp"
#include "injector.hpp"
#include "logger.hpp"

int main()
{
    std::cout << "TheZap" << std::endl;
    sniffer();
    injector();

    tools::logger(tools::log::sniffer, "hello world", 42, '-', 1.23);
    return EXIT_SUCCESS;
}