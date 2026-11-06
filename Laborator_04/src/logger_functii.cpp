#include "logger_functii.hpp"

#include <iostream>

LoggerFunctii::LoggerFunctii()
    : nume_("(empty)")
{
    std::cout << "    [LoggerFunctii] default constructor\n";
}

LoggerFunctii::LoggerFunctii(const std::string& nume)
    : nume_(nume)
{
    std::cout << "    [LoggerFunctii] constructor \"" << nume_ << "\"\n";
}

LoggerFunctii::LoggerFunctii(const LoggerFunctii& other)
    : nume_(other.nume_)
{
    std::cout << "    [LoggerFunctii] copy constructor \"" << nume_ << "\"\n";
}

LoggerFunctii& LoggerFunctii::operator=(const LoggerFunctii& other)
{
    nume_ = other.nume_;
    std::cout << "    [LoggerFunctii] operator= \"" << nume_ << "\"\n";
    return *this;
}

LoggerFunctii::~LoggerFunctii()
{
    std::cout << "    [LoggerFunctii] destructor \"" << nume_ << "\"\n";
}
