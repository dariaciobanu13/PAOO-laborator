// the bad versions, one demo per argument:
//   ./demo_greseli leak | copiere

#include "afisare.hpp"
#include "contract.hpp"
#include "vestiar.hpp"

#include <cstring>
#include <iostream>
#include <stdexcept>

// ---------- Item 13: manual delete ----------
static void negociazaManual(bool renunta, bool aruncaExceptie)
{
    Contract* contract = creeazaContract("Mutu", 5000);

    if (renunta)
        return;                          // forgot delete: leak
    if (aruncaExceptie)
        throw std::runtime_error("medical failed");   // delete never runs: leak

    contract->semneaza();
    delete contract;
}

static void demoLeak()
{
    titlu("BAD Item 13: manual delete");
    negociazaManual(false, false);
    negociazaManual(true, false);
    try {
        negociazaManual(false, true);
    } catch (const std::exception& e) {
        std::cout << "    caught: " << e.what() << "\n";
    }
    std::cout << "  contracts still alive: " << Contract::inViata()
              << " (the sanitizer lists the leaks at exit)\n";
}

// ---------- Item 14: compiler generated copy of an RAII class ----------
class CheieGresita {
private:
    Vestiar* vestiar_;

public:
    explicit CheieGresita(Vestiar* v) : vestiar_(v) { incuie(vestiar_); }
    ~CheieGresita() { descuie(vestiar_); }
    // no copy decision: the compiler copies the pointer
};

static void demoCopiere()
{
    titlu("BAD Item 14: copying a lock");
    Vestiar vestiar{"Steaua"};
    {
        CheieGresita k1(&vestiar);
        CheieGresita k2(k1);    // same Vestiar*, locked only once
    }                           // both destructors unlock
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "usage: " << argv[0] << " leak | copiere\n";
        return 0;
    }
    if (std::strcmp(argv[1], "leak") == 0)
        demoLeak();
    else if (std::strcmp(argv[1], "copiere") == 0)
        demoCopiere();
    else
        std::cout << "unknown demo: " << argv[1] << "\n";
    return 0;
}
