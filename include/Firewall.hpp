#ifndef FIREWALL_HPP
#define FIREWALL_HPP

#include <string>
#include <vector>
#include <utility>

class Firewall {
public:
    Firewall(const std::string& filename = "data/blocked_ranges.txt");
    bool isBlocked(const std::string& ip);

private:
    std::vector<std::pair<uint32_t, uint32_t>> blockedRanges;
    
    uint32_t ipToNumeric(const std::string& ip);
    void loadBlockedRanges(const std::string& filename);
};

#endif
