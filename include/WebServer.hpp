/**
 * @file WebServer.hpp
 * @brief Defines the WebServer structure for processing requests
 */

#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "Request.hpp"

/**
 * @struct WebServer
 * @brief Represents a web server that processes requests
 * 
 * Each WebServer can handle one request at a time. It tracks
 * processing time and completion status.
 */
struct WebServer {
    private:
        bool isBusy;                    ///< Whether the server is currently processing a request
        Request currentRequest;         ///< The request currently being processed
        int remainingTicks;            ///< Number of clock cycles remaining to complete current request
        int numCompletedRequests;      ///< Total number of requests completed by this server

    public:
        /**
         * @brief Default constructor
         * Initializes server as idle with no completed requests
         */
        WebServer();
        
        /**
         * @brief Checks if the server is available to accept a new request
         * @return true if server is idle and can accept requests, false otherwise
         */
        bool requestOK();
        
        /**
         * @brief Assigns a new request to this server
         * @param request The request to be processed
         */
        void assignRequest(Request request);
        
        /**
         * @brief Advances the server's internal clock by one tick
         * Decrements remaining processing time and checks for completion
         */
        void advanceClock();
        
        /**
         * @brief Checks if the current request is complete and handles cleanup
         * Called automatically by advanceClock()
         */
        void isRequestComplete();
        
        /**
         * @brief Gets the total number of completed requests
         * @return Number of requests this server has completed
         */
        int getCompletedRequests() const;
};

#endif