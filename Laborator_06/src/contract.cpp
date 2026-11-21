#include "contract.hpp"

#include <iostream>

int Contract::inViata_ = 0;

Contract::Contract(const std::string& jucator, int salariu)
    : jucator_(jucator), salariu_(salariu)
{
    ++inViata_;
    std::cout << "    [Contract created: " << jucator_ << "]\n";
}

Contract::~Contract()
{
    --inViata_;
    std::cout << "    [Contract destroyed: " << jucator_ << "]\n";
}

void Contract::semneaza() const
{
    std::cout << "    " << jucator_ << " signs for " << salariu_ << " euro\n";
}

int Contract::inViata()
{
    return inViata_;
}

Contract* creeazaContract(const std::string& jucator, int salariu)
{
    return new Contract(jucator, salariu);
}
