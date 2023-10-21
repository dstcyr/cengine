#include "Profiler.h"

CProfiler::CProfiler(const std::string& functionName) : functionName(functionName)
{
    start_time = std::chrono::high_resolution_clock::now();
}

CProfiler::~CProfiler()
{
    auto end_time = std::chrono::high_resolution_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    std::cout << functionName << " took " << elapsed_time.count() << " microseconds." << std::endl;
}
