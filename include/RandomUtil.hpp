#ifndef RANDOMUTIL_HPP
#define RANDOMUTIL_HPP

#include <string>
#include "Request.hpp"

class RandomUtil {
public:
    static void seed(unsigned int seedValue);
    static std::string randomIP();
    static int randomProcessingTime();
    static char randomJobType();
    static bool shouldGenerateArrival();
    static int randomInt(int min, int max);
    static Request randomRequest();
};

#endif

