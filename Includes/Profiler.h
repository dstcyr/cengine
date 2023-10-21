#pragma once
#include <iostream>
#include <chrono>
#include <string>

class CProfiler
{
public:
    CProfiler(const std::string& functionName);
    ~CProfiler();

private:
    std::string functionName;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
};