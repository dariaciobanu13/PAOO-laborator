#include "item10_return_this.hpp"
#include "afisare.hpp"

#include <iostream>

Scor::Scor(int gazde, int oaspeti)
    : gazde_(gazde), oaspeti_(oaspeti)
{
}

Scor& Scor::operator=(const Scor& rhs)
{
    gazde_ = rhs.gazde_;
    oaspeti_ = rhs.oaspeti_;
    return *this;   // the left-hand object, so it can be assigned again
}

Scor& Scor::operator+=(const Scor& rhs)
{
    gazde_ += rhs.gazde_;
    oaspeti_ += rhs.oaspeti_;
    return *this;
}

Scor& Scor::operator=(int goluri)
{
    gazde_ = goluri;
    oaspeti_ = goluri;
    return *this;
}

void Scor::afiseaza(const char* eticheta) const
{
    std::cout << "  " << eticheta << " = " << gazde_ << "-" << oaspeti_ << "\n";
}

void demoItem10()
{
    titlu("Item 10: operator= returns *this");

    Scor a, b, c(2, 1);
    a = b = c;            // parsed as a = (b = c)
    a.afiseaza("a = b = c, a");
    b.afiseaza("           b");

    a = b = 0;            // operator=(int), chained too
    a.afiseaza("a = b = 0, a");

    (a += Scor(1, 0)) += Scor(0, 3);   // works because += returns Scor&
    a.afiseaza("(a += 1-0) += 0-3, a");

    Scor d(c);            // NOT assignment: d is new, copy constructor
    d = a;                // assignment: d already exists
    d.afiseaza("d");
}
