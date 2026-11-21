#include "item12_copiere_completa.hpp"
#include "afisare.hpp"

#include <iostream>

Jucator::Jucator(const std::string& nume, int numar)
    : nume_(nume), numar_(numar)
{
}

Jucator::Jucator(const Jucator& rhs)
    : nume_(rhs.nume_), numar_(rhs.numar_)
{
    std::cout << "    [Jucator copy constructor]\n";
}

Jucator& Jucator::operator=(const Jucator& rhs)
{
    std::cout << "    [Jucator::operator=]\n";
    nume_ = rhs.nume_;
    numar_ = rhs.numar_;
    return *this;
}

void Jucator::afiseaza() const
{
    std::cout << "  " << nume_ << " #" << numar_;
}

Capitan::Capitan(const std::string& nume, int numar, int aniCapitan, const std::string& banderola)
    : Jucator(nume, numar), aniCapitan_(aniCapitan), banderola_(banderola)
{
}

Capitan::Capitan(const Capitan& rhs)
    : Jucator(rhs),                  // base part: call the base copy constructor
      aniCapitan_(rhs.aniCapitan_),
      banderola_(rhs.banderola_)
{
    std::cout << "    [Capitan copy constructor]\n";
}

Capitan& Capitan::operator=(const Capitan& rhs)
{
    Jucator::operator=(rhs);         // base part: call the base operator=
    aniCapitan_ = rhs.aniCapitan_;
    banderola_ = rhs.banderola_;
    std::cout << "    [Capitan::operator=]\n";
    return *this;
}

void Capitan::afiseaza() const
{
    Jucator::afiseaza();
    std::cout << ", captain for " << aniCapitan_ << " years, armband " << banderola_ << "\n";
}

void demoItem12()
{
    titlu("Item 12: copy all parts");

    Capitan hagi("Hagi", 10, 7, "galbena");
    Capitan copie(hagi);
    copie.afiseaza();

    Capitan popescu("Popescu", 6, 3, "rosie");
    popescu = hagi;
    popescu.afiseaza();

    // don't call operator= from the copy constructor or the other way around;
    // if both share code, put it in a private init() function instead
}
