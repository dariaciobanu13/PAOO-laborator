#include "item5_functii_generate.hpp"
#include "afisare.hpp"

#include <iostream>
#include <type_traits>

int Scor::getGoluri() const
{
    return goluri_;
}

Arbitru::Arbitru(const std::string& nume)
    : nume_(nume)
{
}

const std::string& Arbitru::getNume() const
{
    return nume_;
}

Transfer::Transfer(std::string& club, int suma)
    : club_(club), suma_(suma)
{
}

void Transfer::afiseaza() const
{
    std::cout << "  transfer to " << club_ << " for " << suma_ << "\n";
}

Antrenor::Antrenor(const std::string& nume)
    : nume_(new std::string(nume))
{
}

Antrenor::Antrenor(const Antrenor& other)
    : nume_(new std::string(*other.nume_))
{
}

Antrenor& Antrenor::operator=(const Antrenor& other)
{
    // copy first, so a = a doesn't read memory that was just freed
    std::string* copie = new std::string(*other.nume_);
    delete nume_;
    nume_ = copie;
    return *this;
}

Antrenor::~Antrenor()
{
    delete nume_;
}

void Antrenor::schimbaNume(const std::string& nume)
{
    *nume_ = nume;
}

void Antrenor::afiseaza() const
{
    std::cout << "  coach \"" << *nume_ << "\" at " << nume_ << "\n";
}

void demoItem5()
{
    titlu("Item 5: generated functions");
    std::cout << "  class Scor declares none of them, but all of these work:\n";
    std::cout << "  Scor a; (generated default constructor)\n";
    Scor a;
    std::cout << "  Scor b(a); (generated copy constructor)\n";
    Scor b(a);
    std::cout << "  b = a; (generated operator=)\n";
    b = a;
    std::cout << "  each one calls the same function on the LoggerFunctii member\n";
    std::cout << "  goals: " << b.getGoluri() << "\n";
    std::cout << "  leaving the function (generated destructor):\n";

    titlu("Item 5: what the compiler refuses to generate");
    std::cout << "  Arbitru has a constructor, default constructible? "
              << daNu(std::is_default_constructible<Arbitru>::value) << "\n";
    Arbitru arbitru("Hategan");
    std::cout << "  so it must be given a name: " << arbitru.getNume() << "\n";

    std::string club1 = "Rapid";
    std::string club2 = "Dinamo";
    Transfer transfer1(club1, 100);
    Transfer transfer2(club2, 200);
    transfer1.afiseaza();
    transfer2.afiseaza();
    std::cout << "  Transfer has reference + const, copy constructor? "
              << daNu(std::is_copy_constructible<Transfer>::value) << "\n";
    std::cout << "  Transfer has reference + const, operator=? "
              << daNu(std::is_copy_assignable<Transfer>::value)
              << " (target eroare_atribuire_referinta)\n";
    std::cout << "  Rezerva has a base with private operator=, operator=? "
              << daNu(std::is_copy_assignable<Rezerva>::value) << "\n";

    titlu("Item 5: pointer member, deep copy written by hand");
    Antrenor original("Mircea");
    Antrenor copie(original);
    copie.schimbaNume("Dan");
    original.afiseaza();
    copie.afiseaza();
    std::cout << "  different addresses, the generated copy would share one:"
                 " demo_greseli shallow\n";
    copie = original;
    copie.afiseaza();
}
