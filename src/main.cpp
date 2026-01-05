#include <iostream>
#include "LoadBalancer.hpp"

using namespace std;

int main() {
    int numServers;
    int totalCycles;
    
    cout << "Enter number of servers: ";
    cin >> numServers;
    
    cout << "Enter number of clock cycles: ";
    cin >> totalCycles;
    
    string logFilename = "logs/simulation.log";
    LoadBalancer lb(numServers, logFilename);
    
    lb.run(totalCycles);
    
    cout << "\nSimulation completed!" << endl;
    cout << "Log file saved to: " << logFilename << endl;
    
    return 0;
}
