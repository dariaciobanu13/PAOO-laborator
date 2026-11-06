#ifndef CLASE_GRESITE_HPP
#define CLASE_GRESITE_HPP

// classes written WRONG on purpose, to show what the items protect you from

#include "logger_functii.hpp"

#include <iostream>
#include <string>

// item 4, mistake 1: the constructor forgets the built-in members
class StatisticiGresite {
private:
    std::string jucator_;
    int goluri_;
    int cartonase_;

public:
    explicit StatisticiGresite(const std::string& jucator)
        : jucator_(jucator)
    {
    }

    void afiseaza() const
    {
        std::cout << "  " << jucator_ << ": " << goluri_ << " goals, "
                  << cartonase_ << " cards\n";
    }
};

// item 4, mistake 2: suprafata_ is declared first, so it is initialized first,
// the list lies about the order and lungime_ / latime_ are still garbage
class TerenGresit {
private:
    int suprafata_;
    int lungime_;
    int latime_;

public:
    TerenGresit(int lungime, int latime)
        : lungime_(lungime), latime_(latime), suprafata_(lungime_ * latime_)
    {
    }

    void afiseaza() const
    {
        std::cout << "  field " << lungime_ << " x " << latime_ << " = "
                  << suprafata_ << " m2\n";
    }
};

// item 4: the list says c, b, a but the declaration decides
class OrdineInversa {
private:
    LoggerFunctii a_;
    LoggerFunctii b_;
    LoggerFunctii c_;

public:
    OrdineInversa()
        : c_("c"), b_("b"), a_("a")
    {
    }
};

// item 5, mistake: destructor but no copy functions, the generated ones copy the pointer
class AntrenorShallow {
private:
    int* varsta_;

public:
    explicit AntrenorShallow(int varsta)
        : varsta_(new int(varsta))
    {
    }

    ~AntrenorShallow()
    {
        std::cout << "  destructor: delete " << varsta_ << "\n";
        delete varsta_;
    }

    void schimbaVarsta(int varsta)
    {
        *varsta_ = varsta;
    }

    void afiseaza() const
    {
        std::cout << "  coach aged " << *varsta_ << " at " << varsta_ << "\n";
    }
};

// item 4, mistake 3: two globals in different .cpp files, see ordine_statica_*.cpp
int adversariFiasco();

#endif
