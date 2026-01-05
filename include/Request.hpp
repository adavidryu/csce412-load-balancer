/**
 * @file Request.hpp
 * @brief Defines the Request structure for load balancer requests
 */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <string>

/**
 * @struct Request
 * @brief Represents a web request with IP addresses, processing time, and job type
 * 
 * This structure contains all information needed to process a web request
 * through the load balancer system.
 */
struct Request {
    std::string ipIn;        ///< Incoming IP address of the request
    std::string ipOut;       ///< Outgoing IP address for the request
    int processTime;         ///< Number of clock cycles required to process this request
    char jobType;           ///< Job type: 'S' for streaming or 'P' for processing
    int id;                 ///< Unique identifier for this request
    int arrivalTick;        ///< Clock tick when this request arrived in the system
};

#endif