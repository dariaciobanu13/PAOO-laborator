#include "greseli.hpp"

#include <iostream>
#include <string>
#include <utility>

static void demoLeak()
{
    std::cout << "=== No destructor: memory leak ===\n";
    for (int i = 1; i <= 3; ++i) {
        EchipaFaraDestructor e("Team " + std::to_string(i), 1000);
    }   // the object is gone but its heap memory is still allocated
    std::cout << "Allocations: " << EchipaFaraDestructor::alocari
              << ", frees: 0 -> memory leak\n";
}

static void demoMove()
{
    std::cout << "=== No move constructor: std::move still copies ===\n";
    EchipaFaraMove a("Rapid", 1000);
    EchipaFaraMove b(std::move(a));   // should be a move, but all 1000 slots get copied
}

static void demoCopy()
{
    std::cout << "=== No copy constructor: shallow copy ===\n";
    EchipaFaraCopy original("Steaua", 3);
    original.adaugaJucator("Popescu");
    original.adaugaJucator("Ionescu");

    EchipaFaraCopy copie(original);   // only the pointer is copied
    copie.schimbaJucator(0, "Substitute");

    std::cout << "Original:\n";
    original.afiseaza();
    std::cout << "Copy:\n";
    copie.afiseaza();
    std::cout << "-> SAME address: I changed the copy but the original changed too!\n";
    std::cout << "At the end both destructors call delete[] on the same address"
                 " -> double free (crash)\n";
}

int main(int argc, char* argv[])
{
    std::string demo = argc > 1 ? argv[1] : "";

    if (demo == "leak") {
        demoLeak();
    } else if (demo == "move") {
        demoMove();
    } else if (demo == "copy") {
        demoCopy();
    } else {
        std::cout << "Usage: " << argv[0] << " leak | move | copy\n";
    }
    return 0;
}
