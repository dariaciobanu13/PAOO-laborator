#include "item11_autoatribuire.hpp"
#include "afisare.hpp"

#include <iostream>
#include <utility>

Sigla::Sigla(const std::string& desen)
    : desen_(desen)
{
}

Sigla::Sigla(const Sigla& other)
    : desen_(other.desen_)
{
    std::cout << "    [Sigla copied: " << desen_ << "]\n";
}

const std::string& Sigla::getDesen() const
{
    return desen_;
}

// ---------- solution 1: identity test ----------

EchipaTestIdentitate::EchipaTestIdentitate(const std::string& nume, const std::string& desen)
    : nume_(nume), sigla_(new Sigla(desen))
{
}

EchipaTestIdentitate::EchipaTestIdentitate(const EchipaTestIdentitate& other)
    : nume_(other.nume_), sigla_(new Sigla(*other.sigla_))
{
}

EchipaTestIdentitate& EchipaTestIdentitate::operator=(const EchipaTestIdentitate& rhs)
{
    if (this == &rhs) {     // same object: nothing to do
        std::cout << "    identity test: same object, skip\n";
        return *this;
    }
    nume_ = rhs.nume_;
    delete sigla_;
    sigla_ = new Sigla(*rhs.sigla_);   // if this throws, sigla_ points to deleted memory
    return *this;
}

EchipaTestIdentitate::~EchipaTestIdentitate()
{
    delete sigla_;
}

void EchipaTestIdentitate::afiseaza() const
{
    std::cout << "  " << nume_ << " " << sigla_->getDesen() << "\n";
}

// ---------- solution 2: careful ordering ----------

EchipaOrdine::EchipaOrdine(const std::string& nume, const std::string& desen)
    : nume_(nume), sigla_(new Sigla(desen))
{
}

EchipaOrdine::EchipaOrdine(const EchipaOrdine& other)
    : nume_(other.nume_), sigla_(new Sigla(*other.sigla_))
{
}

EchipaOrdine& EchipaOrdine::operator=(const EchipaOrdine& rhs)
{
    Sigla* vecheSigla = sigla_;          // remember the old logo
    sigla_ = new Sigla(*rhs.sigla_);     // copy first (if this throws, nothing changed)
    delete vecheSigla;                   // delete after
    nume_ = rhs.nume_;
    return *this;
}

EchipaOrdine::~EchipaOrdine()
{
    delete sigla_;
}

void EchipaOrdine::afiseaza() const
{
    std::cout << "  " << nume_ << " " << sigla_->getDesen() << "\n";
}

// ---------- solution 3: copy and swap ----------

EchipaSwap::EchipaSwap(const std::string& nume, const std::string& desen)
    : nume_(nume), sigla_(new Sigla(desen))
{
}

EchipaSwap::EchipaSwap(const EchipaSwap& other)
    : nume_(other.nume_), sigla_(new Sigla(*other.sigla_))
{
}

void EchipaSwap::swap(EchipaSwap& other) noexcept
{
    using std::swap;
    swap(nume_, other.nume_);
    swap(sigla_, other.sigla_);
}

EchipaSwap& EchipaSwap::operator=(const EchipaSwap& rhs)
{
    EchipaSwap temp(rhs);   // copy (if this throws, *this is untouched)
    swap(temp);             // *this takes the copy, temp takes the old data
    return *this;
}                           // temp destroyed here, deletes the old logo

EchipaSwap& EchipaSwap::operator=(EchipaSwap&& rhs) noexcept
{
    if (this != &rhs) {
        delete sigla_;              // free the old logo, or it leaks
        sigla_ = rhs.sigla_;        // take rhs's logo
        rhs.sigla_ = nullptr;       // rhs owns nothing now
        nume_ = std::move(rhs.nume_);
    }
    return *this;                   // Item 10 again
}

EchipaSwap::~EchipaSwap()
{
    delete sigla_;   // delete nullptr is fine
}

void EchipaSwap::afiseaza() const
{
    std::cout << "  " << nume_ << " " << (sigla_ ? sigla_->getDesen() : "(no logo, moved from)") << "\n";
}

// ---------- demo ----------

void demoItem11()
{
    titlu("Item 11: assignment to self");

    std::cout << "solution 1, identity test:\n";
    EchipaTestIdentitate poli("Poli", "<lup alb-violet>");
    poli = poli;
    poli.afiseaza();

    std::cout << "solution 2, copy first, delete after:\n";
    EchipaOrdine ordine[2] = {EchipaOrdine("UTA", "<batrana doamna>"),
                              EchipaOrdine("CFR", "<locomotiva>")};
    int i = 0, j = 0;
    ordine[i] = ordine[j];   // hidden self-assignment: i == j
    ordine[0].afiseaza();

    std::cout << "solution 3, copy and swap:\n";
    EchipaSwap rapid("Rapid", "<visiniu>");
    EchipaSwap* p1 = &rapid;
    EchipaSwap* p2 = &rapid;
    *p1 = *p2;               // hidden self-assignment: p1 == p2
    rapid.afiseaza();

    std::cout << "move assignment:\n";
    EchipaSwap dinamo("Dinamo", "<caine rosu>");
    dinamo = std::move(rapid);   // no Sigla copy printed
    dinamo.afiseaza();
    rapid.afiseaza();
}
