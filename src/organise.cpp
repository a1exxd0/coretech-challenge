#include <iostream>
#include <unordered_map>
#include <exception>
#include <stdexcept>
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/Packet.h>
#include <pcapplusplus/PcapFileDevice.h>
#include <pcapplusplus/PcapLiveDeviceList.h>
#include <pcapplusplus/Layer.h>
#include <pcapplusplus/TLVData.h>
#include <pcapplusplus/EthLayer.h>
#include <pcapplusplus/TcpLayer.h>
#include <pcapplusplus/UdpLayer.h>
#include <pcapplusplus/DnsLayer.h>
#include <pcapplusplus/Logger.h>

// In terms of data I'll need to extract:
// - Average packet size
// - Total volume of data transmitted
// - Most frequent destination IP
// - Total number of packets broken down by transport layer protocol
// - Any additional insights or anomalies

/**
 * Helper data:
 * - total number of packets
 * - map of dest ip to quantity or something
 * - logger for transport layer types
 */
namespace std {
    template <>
    struct hash<pcpp::IPv4Address> {
        [[nodiscard]] inline std::size_t operator()(const pcpp::IPv4Address& ip) const noexcept {
            return std::hash<uint32_t>{}(ip.toInt());
        }
    };
}

[[nodiscard]] inline bool operator==(const pcpp::IPv4Address &a1, const pcpp::IPv4Address &a2) {
    return a1.toInt() == a2.toInt();
}

class organise {
public:
    using address_map = std::unordered_map<pcpp::IPv4Address, size_t>;
    using protocol_map = std::unordered_map<pcpp::ProtocolType, size_t>;

private:
    pcpp::RawPacket _packet;
    pcpp::PcapFileReaderDevice reader;
    size_t total_packets;
    size_t total_volume;
    size_t total_payload;
    size_t suspicious_packets;
    address_map _address_map;
    protocol_map _protocol_map;

public:

    [[nodiscard]] size_t getTotalPackets() const noexcept {
        return total_packets;
    }

    [[nodiscard]] size_t getTotalVolume() const noexcept {
        return total_volume;
    }

    [[nodiscard]] size_t getTotalPayload() const noexcept {
        return total_payload;
    }

    [[nodiscard]] size_t getSuspiciousPackets() const noexcept {
        return suspicious_packets;
    }

    [[nodiscard]] const address_map& getAddressMap() const noexcept {
        return _address_map;
    }

    [[nodiscard]] const protocol_map& getProtocolMap() const noexcept {
        return _protocol_map;
    }

    [[nodiscard]] size_t getTCPCount() noexcept {
        return _protocol_map[pcpp::TCP];
    }

    [[nodiscard]] size_t getUDPCount() noexcept {
        return _protocol_map[pcpp::UDP];
    }

    organise(std::string packet_path) : 
        reader(packet_path),
        total_packets(0),
        total_volume(0),
        total_payload(0),
        suspicious_packets(0),
        _address_map(),
        _protocol_map() 
    {
        if (!reader.open()) {
            std::cerr << "Error opening the pcap file" << std::endl;
            throw std::ios_base::failure("Error opening the pcap file");
        }
    }

    ~organise() {
        reader.close();
    }

    bool read_packet() {
        if (!reader.getNextPacket(_packet)) {
            return false;
        }

        pcpp::Packet parsed(&_packet);

        bool is_ipv4 = parsed.isPacketOfType(pcpp::IPv4);
        bool is_tcp = parsed.isPacketOfType(pcpp::TCP);
        bool is_udp = parsed.isPacketOfType(pcpp::UDP);

        if (!is_ipv4) {
            std::cerr << "Packet found is not IPv4\n";
            return false;
        }

        if (!is_tcp && !is_udp) {
            std::cerr << "Packet has unrecognised transport layer\n";
            return false;
        }

        if (is_tcp && is_udp) {
            std::cerr << "Detected both UDP and TCP layers\n";
            return false;
        }

        ++total_packets;

        pcpp::IPv4Address dest = parsed.getLayerOfType<pcpp::IPv4Layer>()->getDstIPv4Address();
        _address_map[dest]++;

        if (is_tcp) {
            pcpp::TcpLayer* tcpLayer = parsed.getLayerOfType<pcpp::TcpLayer>();
            _protocol_map[pcpp::TCP]++;
            total_volume += tcpLayer->getDataLen();
            total_payload += tcpLayer->getLayerPayloadSize();
        } else {
            pcpp::UdpLayer* udpLayer = parsed.getLayerOfType<pcpp::UdpLayer>();
            _protocol_map[pcpp::UDP]++;
            total_volume += udpLayer->getDataLen();
            total_payload += udpLayer->getLayerPayloadSize();
        }

        return true;
    }

};