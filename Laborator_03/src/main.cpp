#include "echipa.hpp"

#include <iostream>
#include <utility>
#include <vector>

static void titlu(const std::string& text)
{
    std::cout << "\n========== " << text << " ==========\n";
}

// takes the team by value -> copy constructor gets called
static void afiseazaPrinValoare(Echipa e)
{
    std::cout << "  inside the function (working on a copy):\n";
    e.afiseaza();
}   // the copy is destroyed here

int main()
{
    titlu("2. Encapsulation");
    Echipa echipa("Steaua", 3);
    echipa.adaugaJucator("Popescu");
    echipa.adaugaJucator("Ionescu");
    echipa.adaugaJucator("Georgescu");
    echipa.adaugaJucator("Marinescu");   // rejected, team is full
    // echipa.nrJucatori_ = 100;         // doesn't compile, nrJucatori_ is private
    std::cout << "  number of players (from getter): " << echipa.getNrJucatori() << "\n";
    echipa.afiseaza();

    titlu("3. Member initialization in the constructor");
    // nume_ is const, so it can't be assigned in the constructor body,
    // it has to go in the initializer list
    std::cout << "  team name (const member): " << echipa.getNume() << "\n";

    titlu("4. Destructor frees the heap");
    {
        Echipa temporara("Temp", 2);
        temporara.adaugaJucator("Vasilescu");
        std::cout << "  leaving the block...\n";
    }   // destructor is called automatically here
    std::cout << "  out of the block, memory was freed\n";

    titlu("5. Copy constructor (deep copy)");
    Echipa copie(echipa);
    copie.schimbaJucator(0, "Substitute");
    std::cout << "  original:\n";
    echipa.afiseaza();
    std::cout << "  copy (changed):\n";
    copie.afiseaza();
    std::cout << "  -> different addresses, the original did NOT change\n";
    afiseazaPrinValoare(echipa);

    titlu("6. Move constructor");
    Echipa mutata(std::move(copie));
    std::cout << "  source after move:\n";
    copie.afiseaza();
    std::cout << "  destination:\n";
    mutata.afiseaza();

    std::cout << "\n  vector<Echipa>: when it grows, elements are MOVED, not copied\n";
    std::vector<Echipa> campionat;
    campionat.push_back(Echipa("Rapid", 2));    // temporary object -> move
    campionat.push_back(Echipa("Dinamo", 2));   // vector grows and moves "Rapid"

    titlu("End of main: everything gets destroyed");
    return 0;
}
