/**
 * @file RandomUtil.hpp
 * @brief Defines utility functions for random number generation
 */

#ifndef RANDOMUTIL_HPP
#define RANDOMUTIL_HPP

#include <string>
#include "Request.hpp"

/**
 * @class RandomUtil
 * @brief Provides static methods for generating random values
 * 
 * Centralizes all randomness in the system for consistency and testability.
 * Uses a single random number generator that can be seeded for reproducible runs.
 */
class RandomUtil {
public:
    /**
     * @brief Seeds the random number generator
     * @param seedValue Seed value for reproducible randomness
     */
    static void seed(unsigned int seedValue);
    
    /**
     * @brief Generates a random IP address
     * @return IP address in dotted decimal format (e.g., "192.168.1.1")
     */
    static std::string randomIP();
    
    /**
     * @brief Generates a random processing time
     * @return Random integer between 1 and 10 (inclusive)
     */
    static int randomProcessingTime();
    
    /**
     * @brief Generates a random job type
     * @return 'S' for streaming or 'P' for processing
     */
    static char randomJobType();
    
    /**
     * @brief Determines if a new request should be generated this tick
     * @return true with 30% probability, false otherwise
     */
    static bool shouldGenerateArrival();
    
    /**
     * @brief Generates a random integer in a range
     * @param min Minimum value (inclusive)
     * @param max Maximum value (inclusive)
     * @return Random integer between min and max
     */
    static int randomInt(int min, int max);
    
    /**
     * @brief Generates a complete random request
     * @return Request with random IP addresses, processing time, and job type
     */
    static Request randomRequest();
};

#endif

