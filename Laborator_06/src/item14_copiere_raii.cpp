#include "item14_copiere_raii.hpp"
#include "afisare.hpp"

#include <iostream>
#include <type_traits>
#include <utility>

// ---------- 1. prohibit copying ----------

CheieUnica::CheieUnica(Vestiar* v)
    : vestiar_(v)
{
    incuie(vestiar_);
}

CheieUnica::~CheieUnica()
{
    descuie(vestiar_);
}

// ---------- 2. reference counting ----------

CheieComuna::CheieComuna(Vestiar* v)
    : vestiar_(v, descuie)   // deleter: called by the last copy
{
    incuie(v);
}

long CheieComuna::folositori() const
{
    return vestiar_.use_count();
}

// ---------- 3. deep copy ----------

ListaJucatori::ListaJucatori(std::size_t marime)
    : numere_(new int[marime]()), marime_(marime)
{
}

ListaJucatori::ListaJucatori(const ListaJucatori& other)
    : numere_(new int[other.marime_]), marime_(other.marime_)
{
    for (std::size_t i = 0; i < marime_; ++i)
        numere_[i] = other.numere_[i];
}

void ListaJucatori::swap(ListaJucatori& other) noexcept
{
    std::swap(numere_, other.numere_);
    std::swap(marime_, other.marime_);
}

ListaJucatori& ListaJucatori::operator=(const ListaJucatori& rhs)
{
    ListaJucatori temp(rhs);   // Item 11: copy and swap
    swap(temp);
    return *this;              // Item 10
}

ListaJucatori::~ListaJucatori()
{
    delete[] numere_;          // new[] goes with delete[]
}

int& ListaJucatori::operator[](std::size_t i)
{
    return numere_[i];
}

void ListaJucatori::afiseaza(const char* eticheta) const
{
    std::cout << "  " << eticheta << ":";
    for (std::size_t i = 0; i < marime_; ++i)
        std::cout << " " << numere_[i];
    std::cout << "\n";
}

// ---------- 4. transfer ownership ----------

CheieTransferabila::CheieTransferabila(Vestiar* v)
    : vestiar_(v)
{
    incuie(vestiar_);
}

CheieTransferabila::~CheieTransferabila()
{
    if (vestiar_)   // a moved-from key owns nothing
        descuie(vestiar_);
}

CheieTransferabila::CheieTransferabila(CheieTransferabila&& other) noexcept
    : vestiar_(other.vestiar_)
{
    other.vestiar_ = nullptr;
}

CheieTransferabila& CheieTransferabila::operator=(CheieTransferabila&& rhs) noexcept
{
    if (this != &rhs) {
        if (vestiar_)
            descuie(vestiar_);    // release what we held before
        vestiar_ = rhs.vestiar_;
        rhs.vestiar_ = nullptr;
    }
    return *this;
}

bool CheieTransferabila::areVestiar() const
{
    return vestiar_ != nullptr;
}

// ---------- demo ----------

void demoItem14()
{
    titlu("Item 14: copying RAII objects");

    std::cout << "1. prohibit copying:\n";
    Vestiar gazde{"Steaua"};
    {
        CheieUnica cheie(&gazde);
        // CheieUnica copie(cheie);   // error: use of deleted function
        std::cout << "  copyable? " << daNu(std::is_copy_constructible<CheieUnica>::value) << "\n";
    }

    std::cout << "2. reference counting:\n";
    Vestiar oaspeti{"Dinamo"};
    {
        CheieComuna c1(&oaspeti);
        {
            CheieComuna c2(c1);
            std::cout << "  two keys, users = " << c1.folositori() << "\n";
        }
        std::cout << "  c2 gone, still locked, users = " << c1.folositori() << "\n";
    }
    std::cout << "  locked now? " << daNu(oaspeti.incuiat) << "\n";

    std::cout << "3. deep copy:\n";
    ListaJucatori titulari(3);
    titulari[0] = 1; titulari[1] = 10; titulari[2] = 9;
    ListaJucatori copie(titulari);
    copie[2] = 99;
    titulari.afiseaza("original");
    copie.afiseaza("copy    ");

    std::cout << "4. transfer ownership:\n";
    Vestiar arbitri{"Arbitri"};
    {
        CheieTransferabila a(&arbitri);
        CheieTransferabila b(std::move(a));
        std::cout << "  after move: a has it? " << daNu(a.areVestiar())
                  << ", b has it? " << daNu(b.areVestiar()) << "\n";
    }   // only b unlocks
}
