#include <iostream>
#include <pcapplusplus/IPv4Layer.h>
#include <pcapplusplus/Packet.h>
#include <pcapplusplus/PcapFileDevice.h>
#include "organise.cpp"

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


int main() {
    std::ios::sync_with_stdio(false); 
    std::cin.tie(nullptr); 
    std::cout.tie(nullptr);
    std::cerr.tie(nullptr);
    
    std::string input_file = "../testfiles/packet-storm.pcap";
    organise o(input_file);

    std::ofstream nullStream("/dev/null");
    std::streambuf* coutBuf = std::cout.rdbuf();
    std::cout.rdbuf(nullStream.rdbuf());

    std::streambuf* cerrBuf = std::cerr.rdbuf();
    std::cerr.rdbuf(nullStream.rdbuf());

    while (o.read_packet());

    std::cout.rdbuf(coutBuf);
    std::cerr.rdbuf(cerrBuf);

    const organise::address_map &m = o.getAddressMap();
    pcpp::IPv4Address mostCommon;
    size_t occurences = 0;
    for (const auto &[addr, q]: m) {
        if (q > occurences) {
            mostCommon = addr;
            occurences = q;
        }
    }

    double averagePacketSize = 
        static_cast<double>(o.getTotalVolume()) / static_cast<double>(o.getTotalPackets());
    double totalVolume = 
        static_cast<double>(o.getTotalVolume()) / static_cast<double>(1024 * 1024);
    double totalPayload = 
        static_cast<double>(o.getTotalPayload()) / static_cast<double>(1024 * 1024);
        
    std::cout << "Average packet size: " << averagePacketSize << " bytes.\n";
    std::cout << "Total volume size: " << totalVolume << " megabytes\n";
    std::cout << "Total payload size: " << totalPayload << " megabytes\n";
    std::cout << "Most frequent IP: " << mostCommon.toString() << "\n";
    std::cout << "TCP-based packet count: " << o.getTCPCount() << "\n";
    std::cout << "UDP-based packet count: " << o.getUDPCount() << "\n";
    return 0;
}