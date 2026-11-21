// the bad versions, one demo per argument:
//   ./demo_greseli void | autoatribuire | copiere

#include "afisare.hpp"
#include "item12_copiere_completa.hpp" // reuses Jucator

#include <cstring>
#include <iostream>
#include <string>

// ---------- Item 10: operator= that returns void ----------
class ScorVoid {
private:
    int goluri_;

public:
    ScorVoid(int goluri = 0) : goluri_(goluri) {}
    void operator=(const ScorVoid& rhs) { goluri_ = rhs.goluri_; }   // bad: returns nothing
    int get() const { return goluri_; }
};

static void demoVoid()
{
    titlu("BAD Item 10: operator= returns void");
    ScorVoid a, b, c(3);
    b = c;          // a single assignment still works
    // a = b = c;   // error: b = c is void, there is nothing to assign to a
    a = b;
    std::cout << "  a = " << a.get() << ", but a = b = c does not compile (uncomment it)\n";
}

// ---------- Item 11: delete first, then copy ----------
// trofee_ is a plain int on the heap, so the sanitizer sees the bad read
class EchipaGresita {
private:
    std::string nume_;
    int* trofee_;

public:
    EchipaGresita(const std::string& nume, int trofee)
        : nume_(nume), trofee_(new int(trofee)) {}
    EchipaGresita(const EchipaGresita& other)
        : nume_(other.nume_), trofee_(new int(*other.trofee_)) {}
    ~EchipaGresita() { delete trofee_; }

    EchipaGresita& operator=(const EchipaGresita& rhs)
    {
        delete trofee_;                    // if &rhs == this, this also deletes rhs.trofee_
        trofee_ = new int(*rhs.trofee_);   // reads deleted memory: undefined behavior
        nume_ = rhs.nume_;
        return *this;
    }
    void afiseaza() const { std::cout << "  " << nume_ << ", " << *trofee_ << " trophies\n"; }
};

static void demoAutoatribuire()
{
    titlu("BAD Item 11: delete first, then copy");
    EchipaGresita steaua("Steaua", 26);
    EchipaGresita& alias = steaua;
    std::cout << "  steaua = alias (same object), the sanitizer should stop here:\n";
    steaua = alias;
    steaua.afiseaza();
}

// ---------- Item 12: copy functions that forget the base part ----------
class CapitanGresit : public Jucator {
private:
    int aniCapitan_;

public:
    CapitanGresit(const std::string& nume, int numar, int aniCapitan)
        : Jucator(nume, numar), aniCapitan_(aniCapitan) {}

    CapitanGresit(const CapitanGresit& rhs)
        : aniCapitan_(rhs.aniCapitan_)     // forgot Jucator(rhs): default constructor runs
    {
    }

    CapitanGresit& operator=(const CapitanGresit& rhs)
    {
        aniCapitan_ = rhs.aniCapitan_;     // forgot Jucator::operator=(rhs): base part unchanged
        return *this;
    }

    void afiseaza() const override
    {
        Jucator::afiseaza();
        std::cout << ", captain for " << aniCapitan_ << " years\n";
    }
};

static void demoCopiere()
{
    titlu("BAD Item 12: base part not copied");
    CapitanGresit hagi("Hagi", 10, 7);
    std::cout << "original:\n";
    hagi.afiseaza();

    CapitanGresit copie(hagi);
    std::cout << "copy constructor (name and number lost):\n";
    copie.afiseaza();

    CapitanGresit popescu("Popescu", 6, 3);
    popescu = hagi;
    std::cout << "after popescu = hagi (still Popescu #6, only the years changed):\n";
    popescu.afiseaza();
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "usage: " << argv[0] << " void | autoatribuire | copiere\n";
        return 0;
    }
    if (std::strcmp(argv[1], "void") == 0)
        demoVoid();
    else if (std::strcmp(argv[1], "autoatribuire") == 0)
        demoAutoatribuire();
    else if (std::strcmp(argv[1], "copiere") == 0)
        demoCopiere();
    else
        std::cout << "unknown demo: " << argv[1] << "\n";
    return 0;
}
