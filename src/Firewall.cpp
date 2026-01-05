/**
 * @file Firewall.cpp
 * @brief Implementation of the Firewall class for IP address blocking
 */

#include "Firewall.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Firewall::Firewall(const std::string& filename) {
    loadBlockedRanges(filename);
}

bool Firewall::isBlocked(const std::string& ip) {
    uint32_t numericIP = ipToNumeric(ip);
    
    for (const auto& range : blockedRanges) {
        if (numericIP >= range.first && numericIP <= range.second) {
            return true;
        }
    }
    
    return false;
}

uint32_t Firewall::ipToNumeric(const std::string& ip) {
    std::istringstream iss(ip);
    std::string segment;
    uint32_t result = 0;
    int shift = 24;
    
    while (std::getline(iss, segment, '.')) {
        uint32_t octet = std::stoul(segment);
        result |= (octet << shift);
        shift -= 8;
    }
    
    return result;
}

void Firewall::loadBlockedRanges(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open file " << filename << std::endl;
        return;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        // Skip empty lines
        if (line.empty() || line.find_first_not_of(" \t") == std::string::npos) {
            continue;
        }
        
        // Parse range: format is "startIP-endIP" or "startIP endIP"
        size_t dashPos = line.find('-');
        size_t spacePos = line.find(' ');
        
        if (dashPos != std::string::npos) {
            // Format: "startIP-endIP"
            std::string startIP = line.substr(0, dashPos);
            std::string endIP = line.substr(dashPos + 1);
            
            // Trim whitespace
            startIP.erase(0, startIP.find_first_not_of(" \t"));
            startIP.erase(startIP.find_last_not_of(" \t") + 1);
            endIP.erase(0, endIP.find_first_not_of(" \t"));
            endIP.erase(endIP.find_last_not_of(" \t") + 1);
            
            uint32_t start = ipToNumeric(startIP);
            uint32_t end = ipToNumeric(endIP);
            
            blockedRanges.push_back(std::make_pair(start, end));
        } else if (spacePos != std::string::npos) {
            // Format: "startIP endIP"
            std::string startIP = line.substr(0, spacePos);
            std::string endIP = line.substr(spacePos + 1);
            
            // Trim whitespace
            startIP.erase(0, startIP.find_first_not_of(" \t"));
            startIP.erase(startIP.find_last_not_of(" \t") + 1);
            endIP.erase(0, endIP.find_first_not_of(" \t"));
            endIP.erase(endIP.find_last_not_of(" \t") + 1);
            
            uint32_t start = ipToNumeric(startIP);
            uint32_t end = ipToNumeric(endIP);
            
            blockedRanges.push_back(std::make_pair(start, end));
        } else {
            // Single IP (treat as range with start == end)
            std::string ip = line;
            ip.erase(0, ip.find_first_not_of(" \t"));
            ip.erase(ip.find_last_not_of(" \t") + 1);
            
            uint32_t numericIP = ipToNumeric(ip);
            blockedRanges.push_back(std::make_pair(numericIP, numericIP));
        }
    }
    
    file.close();
}

