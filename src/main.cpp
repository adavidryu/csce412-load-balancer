#include <iostream>
#include "Request.hpp"
#include "Firewall.hpp"
#include "WebServer.hpp"

using namespace std;

int main() {
    // Test Request creation and printing
    Request req;
    req.ipIn = "192.168.1.50";
    req.ipOut = "10.0.0.1";
    req.processTime = 5;
    req.jobType = 'A';
    
    cout << "Testing Request:" << endl;
    cout << "IP In: " << req.ipIn << endl;
    cout << "IP Out: " << req.ipOut << endl;
    cout << "Process Time: " << req.processTime << endl;
    cout << "Job Type: " << req.jobType << endl;
    cout << endl;
    
    // Create firewall instance (loads blocked ranges from file)
    Firewall firewall;
    
    // Test with two hardcoded IPs
    string testIP1 = "192.168.1.100";
    string testIP2 = "10.0.0.5";
    
    cout << "Testing Firewall:" << endl;
    cout << "IP " << testIP1 << " is " 
         << (firewall.isBlocked(testIP1) ? "BLOCKED" : "ALLOWED") << endl;
    cout << "IP " << testIP2 << " is " 
         << (firewall.isBlocked(testIP2) ? "BLOCKED" : "ALLOWED") << endl;

    // WebServer checkpoint test: Create a WebServer, assign a request with time=3, tick 3 times, confirm it becomes idle.
    cout << "Testing WebServer:" << endl;
    WebServer ws;
    
    // Create a request with processTime=3
    Request testReq;
    testReq.ipIn = "192.168.1.10";
    testReq.ipOut = "10.0.0.2";
    testReq.processTime = 3;
    testReq.jobType = 'B';
    
    cout << "Initial state - Server available: " << (ws.requestOK() ? "YES" : "NO") << endl;
    
    // Assign the request
    ws.assignRequest(testReq);
    cout << "After assigning request (time=3) - Server available: " << (ws.requestOK() ? "YES" : "NO") << endl;
    
    // Tick 3 times
    for (int i = 1; i <= 3; i++) {
        ws.advanceClock();
        cout << "After tick " << i << " - Server available: " << (ws.requestOK() ? "YES" : "NO") << endl;
    }
    
    cout << "Final state - Server idle: " << (ws.requestOK() ? "YES" : "NO") << endl;
    cout << endl;
    
    return 0;
}
