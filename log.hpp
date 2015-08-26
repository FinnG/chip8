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

#define LOG() Log().get(__CLASS_NAME__)

enum class LogCat
{
    CPU,
    ERROR,
    INFO,
    WARNING,
    DISPLAY,
    RAM,
    OTHER,
};

// std::string logcat_to_str(LogCat cat)
// {
//     switch(cat) {
//     case LogCat::CPU: return "CPU";
//     case LogCat::ERROR: return "ERROR";
//     case LogCat::INFO: return "INFO";
//     case LogCat::WARNING: return "WARNING";
//     case LogCat::DISPLAY: return "DISPLAY";
//     case LogCat::RAM: return "RAM";
//     case LogCat::OTHER: return "OTHER";
//     default: return "Unknown";
//     }
// }

class Log
{    
public:    
    Log() {}

    ~Log()
    {
        std::cerr << os.str() << std::endl;
    }
            
    
    std::ostringstream& get(const std::string& where)
    {
        os << where << ": ";
        return os;
    }

private:
    std::ostringstream os;
};

#endif
