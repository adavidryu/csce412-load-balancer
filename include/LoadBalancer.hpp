/**
 * @file LoadBalancer.hpp
 * @brief Defines the LoadBalancer structure for managing requests and servers
 */

#ifndef LOADBALANCER_HPP
#define LOADBALANCER_HPP

#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include "Request.hpp"
#include "WebServer.hpp"
#include "Firewall.hpp"

/**
 * @struct LoadBalancer
 * @brief Main load balancer that manages request queue and web servers
 * 
 * The LoadBalancer coordinates the entire simulation:
 * - Maintains a queue of incoming requests
 * - Manages multiple web servers
 * - Handles dynamic scaling based on queue size
 * - Filters requests through firewall
 * - Logs all activity
 */
struct LoadBalancer {
    private:
        std::queue<Request> q;
        std::vector<WebServer> ws;
        int currentTick;
        int cooldown;
        int lastScaleTick;
        Firewall firewall;
        std::ofstream logStream;
        int requestsAddedThisTick;
        int requestsBlockedThisTick;
        std::string scaleMessage;
        int streamingInQueue;
        int processingInQueue;
        
        void updateJobTypeCounts();
        void generateInitialQueue(int numServers);
        void maybeGenerateNewRequestsEachTick();
        void dispatchRequestsToIdleServers();
        void tickAllServers();
        void scalingCheckAndApplyIfCooldownPassed();
        void logTick();
        
    public:
        /**
         * @brief Constructor that initializes the load balancer
         * @param initialServerCount Number of web servers to start with
         * @param logFilename Path to the log file (default: "logs/simulation.log")
         * @param cooldownValue Number of ticks to wait between scaling operations (default: 10)
         */
        LoadBalancer(int initialServerCount, const std::string& logFilename = "logs/simulation.log", int cooldownValue = 10);
        
        /**
         * @brief Runs the load balancer simulation
         * @param totalCycles Number of clock cycles to run the simulation
         */
        void run(int totalCycles);
};

#endif