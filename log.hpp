#ifndef LOG_HPP
#define LOG_HPP

#include <iostream>
#include <sstream>
#include <string>

inline std::string className(const std::string& prettyFunction)
{
    size_t colons = prettyFunction.find("::");
    if (colons == std::string::npos)
        return "[No class]";
    size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
    size_t end = colons - begin;

    return prettyFunction.substr(begin,end);
}

#define __CLASS_NAME__ className(__PRETTY_FUNCTION__)

#define LOG(level) Log().get(__CLASS_NAME__, LogLevel::level)

enum class LogLevel
{
    ERROR,
    WARN,
    INFO,
    DECODE,
};

class Log
{    
public:    
    Log()
    {
        current_level = LogLevel::WARN;
    }

    ~Log()
    {
        std::cerr << os.str() << std::endl;
    }

    std::string level_to_str(LogLevel level)
    {
        switch(level) {
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARN: return "WARN";
        case LogLevel::DECODE: return "DECODE";
        default: return "Unknown";
        }
    }

    std::ostringstream& get(const std::string& where, LogLevel level)
    {
        os << level_to_str(level) << " - " << where << ": ";
        return os;
    }

private:
    std::ostringstream os;
    LogLevel current_level;
};

#endif
