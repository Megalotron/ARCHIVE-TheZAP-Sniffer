#pragma once

#include <string>
#include <map>

namespace network {

/**
 *  @brief network protocol abstraction
 */
enum class protocol {
    UDP,
    TCP
};

/**
 *  @brief associative table between protocol abstraction and its representation as a std::string
 */
const std::map<protocol, std::string> protocol_to_str {
    {protocol::UDP, "UDP"},
    {protocol::TCP, "TCP"}
};

/**
 *  @brief struct that represent a packet content
 */
struct packet {
    network::protocol protocol;
    std::string src_ip;
    std::string dst_ip;
    unsigned short src_port;
    unsigned short dst_port;
    std::vector<uint8_t> payload;
};
}