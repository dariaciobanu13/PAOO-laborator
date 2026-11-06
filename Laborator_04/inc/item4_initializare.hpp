#ifndef ITEM4_INITIALIZARE_HPP
#define ITEM4_INITIALIZARE_HPP

// Item 4: make sure that objects are initialized before they're used

#include "logger_functii.hpp"

#include <string>

// slow: nume_ is default constructed, then assigned in the body
class JucatorAtribuire {
private:
    LoggerFunctii nume_;
    int goluri_;

public:
    JucatorAtribuire(const LoggerFunctii& nume, int goluri);
};

// fast: nume_ is built directly from the argument
class JucatorLista {
private:
    LoggerFunctii nume_;
    int goluri_;

public:
    JucatorLista(const LoggerFunctii& nume, int goluri);
};

// const members and references can only be set in the init list
class Contract {
private:
    const int id_;
    std::string& club_;
    int luni_;

public:
    Contract(int id, std::string& club, int luni);
    void afiseaza() const;
};

// the init list follows the declaration order, so suprafata_ is
// computed from members that already have their values
class Teren {
private:
    int lungime_;
    int latime_;
    int suprafata_;

public:
    Teren(int lungime, int latime);
    void afiseaza() const;
};

class Liga {
private:
    int nrEchipe_;

public:
    Liga();
    int getNrEchipe() const;
};

// Meyers' singleton: the local static is built at the first call
Liga& ligaNationala();

void demoItem4();

#endif
