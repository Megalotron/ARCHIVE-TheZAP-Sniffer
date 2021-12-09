#pragma once

#include <vector>
#include <thread>
#include <mutex>
#include <tins/tins.h>
#include "packet.hpp"

namespace core {

/**
 *  @brief class that is used to sniff packets on the default network interface
 */
class sniffer {
private:
    mutable std::mutex m_mtx{};
    std::vector<network::packet> m_packets{};
    std::string m_interface;
    std::thread m_sniff_process;

    bool callback(Tins::PDU &pdu);
    template<typename T>
    void get_packet(Tins::PDU &pdu, const Tins::IP &ip);
    static std::vector<uint8_t> get_payload(Tins::PDU &pdu);

public:
    sniffer();
    ~sniffer();

    /**
     *  @brief get the packets contained in the buffer of the class
     */
    [[nodiscard]] std::vector<network::packet> get_packets() const;
    /**
     *  @brief pop the packets contained in the buffer of the class
     */
    std::vector<network::packet> pop_packets();
};
}