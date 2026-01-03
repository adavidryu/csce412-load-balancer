#ifndef WEBSERVER_HPP
#define WEBSERVER_HPP

#include "Request.hpp"

struct WebServer {
    private:
        bool isBusy;
        Request currentRequest;
        int remainingTicks;
        int numCompletedRequests;

    public:
        WebServer();
        bool requestOK();
        void assignRequest(Request request);
        void advanceClock();
        void isRequestComplete();
};

#endif