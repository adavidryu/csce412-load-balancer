/**
 * @file Firewall.hpp
 * @brief Defines the Firewall class for IP address blocking
 */

#ifndef FIREWALL_HPP
#define FIREWALL_HPP

#include <string>
#include <vector>
#include <utility>

/**
 * @class Firewall
 * @brief Manages IP address blocking based on blocked ranges from a file
 * 
 * The Firewall class loads IP address ranges from a file and checks
 * if incoming requests should be blocked. This serves as a DOS attack
 * prevention mechanism.
 */
class Firewall {
public:
    /**
     * @brief Constructor that loads blocked IP ranges from a file
     * @param filename Path to the file containing blocked IP ranges (default: "data/blocked_ranges.txt")
     */
    Firewall(const std::string& filename = "data/blocked_ranges.txt");
    
    /**
     * @brief Checks if an IP address is blocked
     * @param ip IP address in dotted decimal format (e.g., "192.168.1.1")
     * @return true if the IP is blocked, false otherwise
     */
    bool isBlocked(const std::string& ip);

private:
    std::vector<std::pair<uint32_t, uint32_t>> blockedRanges; ///< Vector of blocked IP ranges (start, end)
    
    /**
     * @brief Converts an IP address string to numeric format
     * @param ip IP address in dotted decimal format
     * @return 32-bit unsigned integer representation of the IP
     */
    uint32_t ipToNumeric(const std::string& ip);
    
    /**
     * @brief Loads blocked IP ranges from a file
     * @param filename Path to the file containing blocked ranges
     */
    void loadBlockedRanges(const std::string& filename);
};

#endif
