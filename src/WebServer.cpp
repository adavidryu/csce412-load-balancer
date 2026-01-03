#include "WebServer.hpp"

WebServer::WebServer() {
    isBusy = false;
    remainingTicks = 0;
    numCompletedRequests = 0;
}

bool WebServer::requestOK() {
    return !isBusy;
}

void WebServer::assignRequest(Request request) {
    currentRequest = request;
    isBusy = true;
    remainingTicks = request.processTime;
}

void WebServer::advanceClock() {
    if (remainingTicks > 0) {
        remainingTicks -= 1;
    }
    isRequestComplete();
}

void WebServer::isRequestComplete() {
    if (remainingTicks == 0 && isBusy) {
        numCompletedRequests++;
        isBusy = false;
        currentRequest = Request();
    }
}
