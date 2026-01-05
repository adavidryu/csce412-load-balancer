#ifndef LOADBALANCER_HPP
#define LOADBALANCER_HPP

#include <queue>
#include <vector>
#include <fstream>
#include <string>
#include "Request.hpp"
#include "WebServer.hpp"
#include "Firewall.hpp"

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
        LoadBalancer(int initialServerCount, const std::string& logFilename = "logs/simulation.log", int cooldownValue = 10);
        void run(int totalCycles);
};

#endif