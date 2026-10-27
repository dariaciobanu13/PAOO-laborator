#include "echipa.hpp"

#include <iostream>

Echipa::Echipa(const std::string& nume, std::size_t capacitate)
    : nume_(nume),
      jucatori_(new std::string[capacitate]),
      nrJucatori_(0),
      capacitate_(capacitate)
{
    std::cout << "[Constructor] team \"" << nume_ << "\": allocated room for "
              << capacitate_ << " players at " << jucatori_ << "\n";
}

Echipa::~Echipa()
{
    if (jucatori_ == nullptr) {
        // happens after a move, the players belong to another object now
        std::cout << "[Destructor] team \"" << nume_ << "\": nothing to free (moved-from)\n";
        return;
    }
    std::cout << "[Destructor] team \"" << nume_ << "\": freeing players at "
              << jucatori_ << "\n";
    delete[] jucatori_;
}

Echipa::Echipa(const Echipa& other)
    : nume_(other.nume_ + " (copy)"),
      // new memory for the copy, or nullptr if the source was moved-from
      jucatori_(other.jucatori_ != nullptr ? new std::string[other.capacitate_] : nullptr),
      nrJucatori_(other.nrJucatori_),
      capacitate_(other.capacitate_)
{
    for (std::size_t i = 0; i < nrJucatori_; ++i) {
        jucatori_[i] = other.jucatori_[i];
    }
    std::cout << "[Copy constructor] \"" << other.nume_ << "\": copied " << nrJucatori_
              << " players from " << other.jucatori_ << " to " << jucatori_ << "\n";
}

Echipa::Echipa(Echipa&& other) noexcept
    : nume_(other.nume_),
      jucatori_(other.jucatori_),      // just take the pointer
      nrJucatori_(other.nrJucatori_),
      capacitate_(other.capacitate_)
{
    // the old object doesn't own the memory anymore
    other.jucatori_ = nullptr;
    other.nrJucatori_ = 0;
    other.capacitate_ = 0;
    std::cout << "[Move constructor] \"" << nume_ << "\": took the players from "
              << jucatori_ << ", nothing copied\n";
}

bool Echipa::adaugaJucator(const std::string& jucator)
{
    if (nrJucatori_ >= capacitate_) {
        std::cout << "  team \"" << nume_ << "\" is full, can't add "
                  << jucator << "\n";
        return false;
    }
    jucatori_[nrJucatori_++] = jucator;
    return true;
}

void Echipa::schimbaJucator(std::size_t index, const std::string& jucatorNou)
{
    if (index < nrJucatori_) {
        jucatori_[index] = jucatorNou;
    }
}

const std::string& Echipa::getNume() const
{
    return nume_;
}

std::size_t Echipa::getNrJucatori() const
{
    return nrJucatori_;
}

void Echipa::afiseaza() const
{
    std::cout << "  team \"" << nume_ << "\" (players at " << jucatori_ << "): ";
    if (nrJucatori_ == 0) {
        std::cout << "(no players)";
    }
    for (std::size_t i = 0; i < nrJucatori_; ++i) {
        std::cout << jucatori_[i] << (i + 1 < nrJucatori_ ? ", " : "");
    }
    std::cout << "\n";
}
