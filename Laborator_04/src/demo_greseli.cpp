#include "clase_gresite.hpp"
#include "item4_initializare.hpp"

#include <cstring>
#include <iostream>
#include <new>
#include <string>
#include <utility>

// reading uninitialized memory is undefined behaviour and the stack is often
// full of zeros, which would hide the bug, so fill it with a visible pattern
template <typename T, typename... Argumente>
static void afiseazaPeMemorieMurdara(Argumente&&... argumente)
{
    alignas(T) unsigned char memorie[sizeof(T)];
    std::memset(memorie, 0xAB, sizeof(memorie));

    T* obiect = new (memorie) T(std::forward<Argumente>(argumente)...);
    obiect->afiseaza();
    obiect->~T();
}

static void demoNeinitializat()
{
    std::cout << "=== Item 4: members left uninitialized ===\n";
    static int goluriStatic;    // static, so it starts at 0
    std::cout << "  static int: " << goluriStatic << "\n";
    afiseazaPeMemorieMurdara<StatisticiGresite>("Popescu");
    std::cout << "-> the numbers are whatever was already in memory\n";
}

static void demoOrdine()
{
    std::cout << "=== Item 4: init list in the wrong order ===\n";
    afiseazaPeMemorieMurdara<TerenGresit>(105, 68);
    std::cout << "-> 105 x 68 should be 7140, but suprafata_ is initialized first\n";

    std::cout << "List written c, b, a:\n";
    OrdineInversa ordine;
    std::cout << "-> built a, b, c, the order from the class\n";
}

static void demoFiasco()
{
    std::cout << "=== Item 4: static initialization order fiasco ===\n";
    std::cout << "Opponents with a global league: " << adversariFiasco() << "\n";
    std::cout << "Opponents with ligaNationala(): "
              << ligaNationala().getNrEchipe() - 1 << "\n";
    std::cout << "-> the global league wasn't built yet when the club read it\n";
}

static void demoShallow()
{
    std::cout << "=== Item 5: generated copy of a pointer member ===\n";
    AntrenorShallow original(60);
    AntrenorShallow copie(original);    // only the pointer is copied
    copie.schimbaVarsta(45);

    original.afiseaza();
    copie.afiseaza();
    std::cout << "-> SAME address: I changed the copy but the original changed too!\n";
    std::cout << "At the end both destructors call delete on it -> double free (crash)\n";
}

int main(int argc, char* argv[])
{
    // flush after every print, so the output survives the crash
    std::cout << std::unitbuf;

    std::string demo = argc > 1 ? argv[1] : "";

    if (demo == "neinit") {
        demoNeinitializat();
    } else if (demo == "ordine") {
        demoOrdine();
    } else if (demo == "fiasco") {
        demoFiasco();
    } else if (demo == "shallow") {
        demoShallow();
    } else {
        std::cout << "Usage: " << argv[0] << " neinit | ordine | fiasco | shallow\n";
    }
    return 0;
}
