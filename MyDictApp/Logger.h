#pragma once
#include <fstream>
#include <string>
#include <chrono>
#include <iomanip>

using namespace std;


enum class Level { Info, Warning, Error };

class Logger {
public:
    explicit Logger(const wstring& path);
    void log(Level lvl, const wstring& msg);

private:
    wofstream log_;
    wstring levelToWString(Level lvl);
};
