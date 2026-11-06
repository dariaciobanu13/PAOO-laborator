#ifndef LOGGER_FUNCTII_HPP
#define LOGGER_FUNCTII_HPP

#include <string>

// prints every special function that gets called on it
// put it inside a class to see what the compiler calls behind your back
class LoggerFunctii {
private:
    std::string nume_;

public:
    LoggerFunctii();
    explicit LoggerFunctii(const std::string& nume);
    LoggerFunctii(const LoggerFunctii& other);
    LoggerFunctii& operator=(const LoggerFunctii& other);
    ~LoggerFunctii();
};

#endif
