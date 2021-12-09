#include <map>
#include <typeindex>
#include "sniffer.hpp"
#include "logger.hpp"

const std::map<std::type_index, network::protocol> protocol_map {
    {typeid(Tins::TCP), network::protocol::TCP},
    {typeid(Tins::UDP), network::protocol::UDP},
};

core::sniffer::sniffer()
    : m_interface(Tins::NetworkInterface::default_interface().name()),
    m_sniff_process([&]() {
        Tins::Sniffer(m_interface).sniff_loop(Tins::make_sniffer_handler(this, &core::sniffer::callback));
    })
{
    tools::logger(tools::log::sniffer, "Sniffer ON, listening on ", m_interface);
}

core::sniffer::~sniffer()
{
    if (m_sniff_process.joinable())
        m_sniff_process.join();
    tools::logger(tools::log::sniffer, "Sniffer OFF");
}

std::vector<network::packet> core::sniffer::get_packets() const
{
    std::scoped_lock mtx(m_mtx);
    return m_packets;
}

std::vector<network::packet> core::sniffer::pop_packets()
{
    std::scoped_lock mtx(m_mtx);
    return std::move(m_packets);
}

std::vector<uint8_t> core::sniffer::get_payload(Tins::PDU &pdu)
{
    try {
        return pdu.rfind_pdu<Tins::RawPDU>().payload();
    } catch (...) {
        return {};
    }
}

template<typename T>
void core::sniffer::get_packet(Tins::PDU &pdu, const Tins::IP &ip)
{
    std::scoped_lock mtx(m_mtx);
    try {
        const auto &protocol = pdu.rfind_pdu<T>();
        m_packets.push_back({protocol_map.at(typeid(T)),
                             ip.src_addr().to_string(),
                             ip.dst_addr().to_string(),
                             protocol.sport(),
                             protocol.dport(),
                             get_payload(pdu)});
    } catch (...) {}
}

bool core::sniffer::callback(Tins::PDU &pdu)
{
    const auto &ip = pdu.rfind_pdu<Tins::IP>();

    get_packet<Tins::TCP>(pdu, ip);
    get_packet<Tins::UDP>(pdu, ip);

    return true;
}
