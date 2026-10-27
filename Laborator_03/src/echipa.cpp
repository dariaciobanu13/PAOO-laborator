#include "echipa.h"

#include <iostream>

Echipa::Echipa(const std::string& numeEchipa, std::size_t cap)
    : nume(numeEchipa),
      jucatori(new std::string[cap]),
      nrJucatori(0),
      capacitate(cap)
{
    std::cout << "[Constructor] team \"" << nume << "\": allocated room for "
              << capacitate << " players at " << jucatori << "\n";
}

Echipa::~Echipa()
{
    std::cout << "[Destructor] team \"" << nume << "\": freeing players at "
              << jucatori << "\n";
    delete[] jucatori;   // ok even if it's nullptr (after a move)
}

Echipa::Echipa(const Echipa& other)
    : nume(other.nume + " (copy)"),
      jucatori(new std::string[other.capacitate]),   // new memory for the copy
      nrJucatori(other.nrJucatori),
      capacitate(other.capacitate)
{
    for (std::size_t i = 0; i < nrJucatori; ++i) {
        jucatori[i] = other.jucatori[i];
    }
    std::cout << "[Copy constructor] \"" << other.nume << "\": copied " << nrJucatori
              << " players from " << other.jucatori << " to " << jucatori << "\n";
}

Echipa::Echipa(Echipa&& other) noexcept
    : nume(other.nume),
      jucatori(other.jucatori),      // just take the pointer
      nrJucatori(other.nrJucatori),
      capacitate(other.capacitate)
{
    // the old object doesn't own the memory anymore
    other.jucatori = nullptr;
    other.nrJucatori = 0;
    other.capacitate = 0;
    std::cout << "[Move constructor] \"" << nume << "\": took the players from "
              << jucatori << ", nothing copied\n";
}

bool Echipa::adaugaJucator(const std::string& jucator)
{
    if (nrJucatori >= capacitate) {
        std::cout << "  team \"" << nume << "\" is full, can't add "
                  << jucator << "\n";
        return false;
    }
    jucatori[nrJucatori++] = jucator;
    return true;
}

void Echipa::schimbaJucator(std::size_t index, const std::string& jucatorNou)
{
    if (index < nrJucatori) {
        jucatori[index] = jucatorNou;
    }
}

const std::string& Echipa::getNume() const
{
    return nume;
}

std::size_t Echipa::getNrJucatori() const
{
    return nrJucatori;
}

void Echipa::afiseaza() const
{
    std::cout << "  team \"" << nume << "\" (players at " << jucatori << "): ";
    if (nrJucatori == 0) {
        std::cout << "(no players)";
    }
    for (std::size_t i = 0; i < nrJucatori; ++i) {
        std::cout << jucatori[i] << (i + 1 < nrJucatori ? ", " : "");
    }
    std::cout << "\n";
}
