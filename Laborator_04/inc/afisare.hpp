#ifndef AFISARE_HPP
#define AFISARE_HPP

#include <iostream>
#include <string>

inline void titlu(const std::string& text)
{
    std::cout << "\n========== " << text << " ==========\n";
}

inline const char* daNu(bool valoare)
{
    return valoare ? "yes" : "no";
}

#endif
