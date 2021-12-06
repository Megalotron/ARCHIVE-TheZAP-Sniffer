#include <iostream>
#include "sniffer.hpp"
#include "injector.hpp"

#include "logger.hpp"

int main()
{
    std::cout << "TheZap" << std::endl;
    sniffer();
    injector();

    tools::logger(log::source::sniffer, "hello ", std::string("world"), 42, 1.23);
    return EXIT_SUCCESS;
}