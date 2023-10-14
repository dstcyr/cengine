#pragma once

typedef enum
{
    LL_VERBOSE,            /**< verbose logs */
    LL_DEBUG,              /**< developper logs */
    LL_WARNING,            /**< potential problems */
    LL_ERROR               /**< errors and crashes */
} ELogLevel;

#if defined(_DEBUG)
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

void LogInternal(ELogLevel level, const char* format, ...);
bool AssertInternal(bool condition, const char* filename, int line);

#define LOG(level, format, ...) LogInternal(level, format, __VA_ARGS__)
#define CHECK(condition) if(AssertInternal(condition, __FILE__, __LINE__)) { DebugBreak(); }
#define FAIL() if(AssertInternal(false, __FILE__, __LINE__)) { DebugBreak(); }

#else
#define LOG(level, format, ...)
#define CHECK(condition)
#define FAIL()
#endif