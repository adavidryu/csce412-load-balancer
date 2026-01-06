/**
 * @file RandomUtil.cpp
 * @brief Implementation of utility functions for random number generation
 */

#include "RandomUtil.hpp"
#include <random>
#include <sstream>

static std::mt19937 gen(std::random_device{}());

void RandomUtil::seed(unsigned int seedValue) {
    gen.seed(seedValue);
}

std::string RandomUtil::randomIP() {
    std::uniform_int_distribution<> dis(1, 254);
    std::ostringstream oss;
    oss << dis(gen) << "." << dis(gen) << "." << dis(gen) << "." << dis(gen);
    return oss.str();
}

int RandomUtil::randomProcessingTime() {
    std::uniform_int_distribution<> dis(1, 10);
    return dis(gen);
}

char RandomUtil::randomJobType() {
    std::uniform_int_distribution<> dis(0, 1);
    return (dis(gen) == 0) ? 'S' : 'P';  // S = streaming, P = processing
}

bool RandomUtil::shouldGenerateArrival() {
    std::uniform_int_distribution<> dis(0, 99);
    return dis(gen) < 30;  // 30% chance per tick - original rate to keep queue active
}

int RandomUtil::randomInt(int min, int max) {
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

Request RandomUtil::randomRequest() {
    Request req;
    req.ipIn = randomIP();
    req.ipOut = randomIP();
    req.processTime = randomProcessingTime();
    req.jobType = randomJobType();
    return req;
}

