#include "Logger.h"
#include <stdexcept>

using namespace std;

Logger::Logger(const wstring& path) {
    log_.open(path, ios::app);
    if (!log_.is_open())
        throw runtime_error("Cannot open log file");
}

void Logger::log(Level lvl, const wstring& msg) {
    auto now = chrono::system_clock::now();
    auto t = chrono::system_clock::to_time_t(now);
    log_ << L"[" << put_time(localtime(&t), L"%F %T") << L"] "
        << levelToWString(lvl) << L": " << msg << L"\n";
    log_.flush();
}

wstring Logger::levelToWString(Level lvl) {
    switch (lvl) {
    case Level::Info:    return L"INFO";
    case Level::Warning: return L"WARNING";
    case Level::Error:   return L"ERROR";
    }
    return L"UNKNOWN";
}
