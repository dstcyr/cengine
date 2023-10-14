#include "Log.h"

#if defined(_DEBUG)
#include <iostream>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <stdio.h>
#include <string>

void ShowDateTime(HANDLE consoleHnd)
{
    std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string output(30, '\0');
    std::strftime(&output[0], output.size(), "%d-%b-%Y %H:%M:%S", std::localtime(&now));

    SetConsoleTextAttribute(consoleHnd, 15);
    std::cout << std::setw(22) << std::left << std::string(output.c_str());
}

void ShowLogLevel(HANDLE consoleHnd, const std::string& level, int color)
{
    SetConsoleTextAttribute(consoleHnd, color);
    std::cout << std::setw(3) << std::left << level;
}

void ShowMessage(HANDLE consoleHnd, const std::string& message, int color)
{
    SetConsoleTextAttribute(consoleHnd, color);
    std::cout << " " << message << std::endl;
}

void LogInternal(ELogLevel level, const char* format, ...)
{
    HANDLE consoleHnd = GetStdHandle(STD_OUTPUT_HANDLE);

    char message[2048];

    va_list args;
    int retval;

    va_start(args, format);
    retval = vsprintf_s(message, format, args);
    va_end(args);

    if (retval > 0 && retval < 2048)
    {
        message[retval] = '\0';
    }

    ShowDateTime(consoleHnd);

    int messageColor = 0;
    int levelColor = 0;
    std::string levelstr;

    switch (level)
    {
    case ELogLevel::LL_VERBOSE:
        levelstr = " V";
        messageColor = 8;
        levelColor = 240;
        break;

    case ELogLevel::LL_DEBUG:
        levelstr = " D";
        messageColor = 10;
        levelColor = 160;
        break;

    case ELogLevel::LL_WARNING:
        levelstr = " W";
        messageColor = 14;
        levelColor = 224;
        break;

    case ELogLevel::LL_ERROR:
        levelstr = " E";
        messageColor = 12;
        levelColor = 192;
        break;
    }

    ShowLogLevel(consoleHnd, levelstr, levelColor);
    ShowMessage(consoleHnd, std::string(message), messageColor);
}

bool AssertInternal(bool condition, const char* filename, int line)
{
    if (!condition)
    {
        char tBuffer[4096];
        char tPrgName[260];
        HWND hWndParent = GetActiveWindow();
        GetModuleFileName(NULL, tPrgName, sizeof(tPrgName));
        const char* tPrg = (strrchr(tPrgName, '\\')) + 1;
        const char* tSrcFile = (strrchr(filename, '\\'));

        if (nullptr == tSrcFile)
        {
            tSrcFile = filename;
        }
        else
        {
            tSrcFile += 1;
        }

        wsprintf(tBuffer, "Assertion failed in %s (%d)", tSrcFile, line);

        int tResult = MessageBox(hWndParent, tBuffer, "Debug Assertion Failed",
            MB_TASKMODAL | MB_SETFOREGROUND |
            MB_ABORTRETRYIGNORE | MB_ICONEXCLAMATION);

        if (tResult == IDABORT)
        {
            exit(0);
        }

        return (tResult == IDRETRY);
    }

    return false;
}

#endif
