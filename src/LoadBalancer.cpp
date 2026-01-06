/**
 * @file LoadBalancer.cpp
 * @brief Implementation of the LoadBalancer structure for managing requests and servers
 */

#include "LoadBalancer.hpp"
#include "RandomUtil.hpp"
#include <iostream>

static int nextRequestId = 1;

LoadBalancer::LoadBalancer(int initialServerCount, const std::string& logFilename, int cooldownValue) 
    : currentTick(0), cooldown(cooldownValue), lastScaleTick(-cooldown), firewall(), 
      requestsAddedThisTick(0), requestsBlockedThisTick(0), scaleMessage(""),
      streamingInQueue(0), processingInQueue(0), initialQueueSize(0), initialServerCount(initialServerCount) {
    
    ws.resize(initialServerCount);
    
    logStream.open(logFilename);
    if (!logStream.is_open()) {
        std::cerr << "Warning: Could not open log file " << logFilename << std::endl;
    }
    
    generateInitialQueue(initialServerCount);
    initialQueueSize = q.size();
}

void LoadBalancer::generateInitialQueue(int numServers) {
    int initialRequests = numServers * 20;
    for (int i = 0; i < initialRequests; i++) {
        Request req = RandomUtil::randomRequest();
        req.id = nextRequestId++;
        req.arrivalTick = 0;
        if (!firewall.isBlocked(req.ipIn)) {
            q.push(req);
        }
    }
}

void LoadBalancer::maybeGenerateNewRequestsEachTick() {
    requestsAddedThisTick = 0;
    requestsBlockedThisTick = 0;
    
    if (RandomUtil::shouldGenerateArrival()) {
        int numNew = RandomUtil::randomInt(1, 3);  // 1-3 requests per arrival
        
        for (int i = 0; i < numNew; i++) {
            Request req = RandomUtil::randomRequest();
            req.id = nextRequestId++;
            req.arrivalTick = currentTick;
            if (!firewall.isBlocked(req.ipIn)) {
                q.push(req);
                requestsAddedThisTick++;
            } else {
                requestsBlockedThisTick++;
            }
        }
    }
}

void LoadBalancer::dispatchRequestsToIdleServers() {
    while (!q.empty()) {
        bool foundIdle = false;
        for (size_t i = 0; i < ws.size(); i++) {
            if (ws[i].requestOK()) {
                ws[i].assignRequest(q.front());
                q.pop();
                foundIdle = true;
                break;
            }
        }
        
        if (!foundIdle) {
            break;
        }
    }
}

void LoadBalancer::tickAllServers() {
    for (auto& server : ws) {
        server.advanceClock();
    }
}

void LoadBalancer::scalingCheckAndApplyIfCooldownPassed() {
    scaleMessage = "";
    
    if (currentTick - lastScaleTick < cooldown) {
        return;
    }
    
    int queueSize = q.size();
    int numServers = ws.size();
    int thresholdHigh = 25 * numServers;  // Adjusted threshold
    int thresholdLow = 15 * numServers;   // Adjusted threshold
    
    if (queueSize > thresholdHigh) {
        ws.push_back(WebServer());
        lastScaleTick = currentTick;
        serversAddedTicks.push_back(currentTick);
        scaleMessage = " [SCALE UP to " + std::to_string(ws.size()) + " servers]";
    }
    else if (queueSize < thresholdLow && numServers > 1) {
        for (size_t i = 0; i < ws.size(); i++) {
            if (ws[i].requestOK()) {
                ws.erase(ws.begin() + i);
                lastScaleTick = currentTick;
                serversRemovedTicks.push_back(currentTick);
                scaleMessage = " [SCALE DOWN to " + std::to_string(ws.size()) + " servers]";
                break;
            }
        }
    }
}

void LoadBalancer::updateJobTypeCounts() {
    streamingInQueue = 0;
    processingInQueue = 0;
    std::queue<Request> tempQueue = q;
    while (!tempQueue.empty()) {
        if (tempQueue.front().jobType == 'S') {
            streamingInQueue++;
        } else if (tempQueue.front().jobType == 'P') {
            processingInQueue++;
        }
        tempQueue.pop();
    }
}

void LoadBalancer::logTick() {
    updateJobTypeCounts();
    int queueSize = q.size();
    int numServers = ws.size();
    int busyServers = 0;
    int totalCompleted = 0;
    
    for (auto& server : ws) {
        if (!server.requestOK()) {
            busyServers++;
        }
        totalCompleted += server.getCompletedRequests();
    }
    
    logStream << "Tick " << currentTick 
              << ": Queue=" << queueSize 
              << " (S=" << streamingInQueue << ", P=" << processingInQueue << ")"
              << ", Servers=" << numServers 
              << " (Busy=" << busyServers << ", Idle=" << (numServers - busyServers) << ")"
              << ", Completed=" << totalCompleted;
    
    if (requestsAddedThisTick > 0) {
        logStream << ", Added=" << requestsAddedThisTick;
    }
    if (requestsBlockedThisTick > 0) {
        logStream << ", Blocked=" << requestsBlockedThisTick;
    }
    if (!scaleMessage.empty()) {
        logStream << scaleMessage;
    }
    
    logStream << std::endl;
}

void LoadBalancer::run(int totalCycles) {
    logStream << "=== Load Balancer Simulation Started ===" << std::endl;
    logStream << "Initial servers: " << ws.size() << std::endl;
    logStream << "Starting queue size: " << initialQueueSize << std::endl;
    logStream << "Task time range: 1-10 clock cycles" << std::endl;
    logStream << "Cooldown: " << cooldown << " ticks" << std::endl;
    logStream << "Total cycles: " << totalCycles << std::endl;
    logStream << "=========================================" << std::endl;
    
    for (int cycle = 0; cycle < totalCycles; cycle++) {
        currentTick = cycle;
        maybeGenerateNewRequestsEachTick();
        dispatchRequestsToIdleServers();
        tickAllServers();
        scalingCheckAndApplyIfCooldownPassed();
        logTick();
    }
    
    int finalQueueSize = q.size();
    
    logStream << "=== Load Balancer Simulation Completed ===" << std::endl;
    logStream << "Final servers: " << ws.size() << std::endl;
    logStream << "Ending queue size: " << finalQueueSize << std::endl;
    
    logStream << "\n=== Scaling Summary ===" << std::endl;
    int netServersChange = ws.size() - initialServerCount;
    logStream << "Initial servers: " << initialServerCount << std::endl;
    logStream << "Final servers: " << ws.size() << std::endl;
    if (netServersChange > 0) {
        logStream << "Net servers added: " << netServersChange << std::endl;
    } else if (netServersChange < 0) {
        logStream << "Net servers removed: " << -netServersChange << std::endl;
    } else {
        logStream << "Net server change: 0 (no change)" << std::endl;
    }
    logStream << "Total scaling events: " << (serversAddedTicks.size() + serversRemovedTicks.size()) 
              << " (" << serversAddedTicks.size() << " additions, " << serversRemovedTicks.size() << " removals)" << std::endl;
    
    logStream.close();
}
