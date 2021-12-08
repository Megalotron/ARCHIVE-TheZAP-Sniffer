#include <iostream>
#include "logger.hpp"
#include "sniffer.hpp"

int main()
{
    core::sniffer sniffer;
    while (true) {
        auto packets = sniffer.pop_packets();
        for (auto &p : packets)
            tools::logger(tools::log::sniffer, " [", network::protocol_to_str.at(p.protocol), "] ", p.src_ip, " -> ", p.dst_ip, " payload size : ", p.payload.size());
    }

    return EXIT_SUCCESS;
}