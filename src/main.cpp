/**
 * @file main.cpp
 * @brief Main entry point for the Load Balancer simulation
 * @author Project 2 Team
 * @date 2024
 * 
 * This program simulates a load balancer managing web requests across
 * multiple servers. It prompts the user for configuration and runs the simulation.
 */

#include <iostream>
#include "LoadBalancer.hpp"

using namespace std;

/**
 * @brief Main function
 * 
 * Prompts user for number of servers and clock cycles, then runs the simulation.
 * 
 * @return 0 on successful completion
 */
int main() {
    int numServers;
    int totalCycles;
    
    cout << "Enter number of servers: ";
    cin >> numServers;
    
    cout << "Enter number of clock cycles: ";
    cin >> totalCycles;
    
    string logFilename = "logs/Log.txt";
    LoadBalancer lb(numServers, logFilename);
    
    lb.run(totalCycles);
    
    cout << "\nSimulation completed!" << endl;
    cout << "Log file saved to: " << logFilename << endl;
    
    return 0;
}
