#include <iostream>
#include "Request.hpp"
#include "Firewall.hpp"

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
    
    return 0;
}
