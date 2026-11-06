#include "item4_initializare.hpp"
#include "afisare.hpp"

#include <iostream>

JucatorAtribuire::JucatorAtribuire(const LoggerFunctii& nume, int goluri)
{
    nume_ = nume;       // nume_ was already default constructed before this line
    goluri_ = goluri;
}

JucatorLista::JucatorLista(const LoggerFunctii& nume, int goluri)
    : nume_(nume), goluri_(goluri)
{
}

Contract::Contract(int id, std::string& club, int luni)
    : id_(id), club_(club), luni_(luni)
{
}

void Contract::afiseaza() const
{
    std::cout << "  contract " << id_ << ": " << club_ << ", " << luni_ << " months\n";
}

Teren::Teren(int lungime, int latime)
    : lungime_(lungime), latime_(latime), suprafata_(lungime_ * latime_)
{
}

void Teren::afiseaza() const
{
    std::cout << "  field " << lungime_ << " x " << latime_ << " = "
              << suprafata_ << " m2\n";
}

Liga::Liga()
    : nrEchipe_(16)
{
}

int Liga::getNrEchipe() const
{
    return nrEchipe_;
}

Liga& ligaNationala()
{
    static Liga liga;   // built here, the first time someone needs it
    return liga;
}

// depends on the league from another global, but it's safe because
// the league comes from a function, not from a global object
static const int adversariGlobal = ligaNationala().getNrEchipe() - 1;

void demoItem4()
{
    titlu("Item 4: assignment vs init list");
    LoggerFunctii nume("Popescu");
    std::cout << "  assignment in the body (2 steps, default + operator=):\n";
    {
        JucatorAtribuire jucator(nume, 3);
    }
    std::cout << "  init list (1 step, copy constructor):\n";
    {
        JucatorLista jucator(nume, 3);
    }

    titlu("Item 4: const and reference members");
    std::string club = "Steaua";
    Contract contract(1, club, 24);
    contract.afiseaza();
    club = "FCSB";      // club_ is a reference, the contract sees the change
    contract.afiseaza();
    std::cout << "  assigning them in the body doesn't compile,"
                 " see target eroare_const_in_corp\n";

    titlu("Item 4: member order");
    Teren teren(105, 68);
    teren.afiseaza();
    std::cout << "  init list in declaration order, the bad version is: demo_greseli ordine\n";

    titlu("Item 4: static initialization order");
    std::cout << "  opponents, computed before main: " << adversariGlobal << "\n";
    std::cout << "  ligaNationala() was built at its first use,"
                 " the bad version is: demo_greseli fiasco\n";
}
