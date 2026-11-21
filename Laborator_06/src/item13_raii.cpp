#include "item13_raii.hpp"
#include "contract.hpp"
#include "afisare.hpp"

#include <iostream>
#include <memory>
#include <stdexcept>

// the contract is handed to a unique_ptr right away (RAII)
// return, exception or normal end: the destructor deletes it
static void negociaza(bool renunta, bool aruncaExceptie)
{
    std::unique_ptr<Contract> contract(creeazaContract("Mutu", 5000));

    if (renunta) {
        std::cout << "    early return\n";
        return;
    }
    if (aruncaExceptie)
        throw std::runtime_error("medical failed");

    contract->semneaza();
}

void demoItem13()
{
    titlu("Item 13: objects manage resources");

    std::cout << "unique_ptr, normal end:\n";
    negociaza(false, false);
    std::cout << "unique_ptr, early return:\n";
    negociaza(true, false);
    std::cout << "unique_ptr, exception:\n";
    try {
        negociaza(false, true);
    } catch (const std::exception& e) {
        std::cout << "    caught: " << e.what() << "\n";
    }
    std::cout << "  contracts still alive: " << Contract::inViata() << "\n";

    std::cout << "unique_ptr, one owner:\n";
    auto p1 = std::make_unique<Contract>("Chivu", 8000);
    // auto p2 = p1;            // error: unique_ptr has no copy
    auto p3 = std::move(p1);    // ownership moves explicitly
    std::cout << "  p1 is " << (p1 ? "not null" : "null") << ", p3 owns it\n";

    std::cout << "shared_ptr, shared owners:\n";
    auto s1 = std::make_shared<Contract>("Lobont", 3000);
    {
        auto s2 = s1;
        std::cout << "  use_count = " << s1.use_count() << "\n";
    }
    std::cout << "  s2 gone, use_count = " << s1.use_count() << "\n";

    std::cout << "arrays: std::vector, or unique_ptr<T[]> (calls delete[]):\n";
    std::unique_ptr<int[]> goluri(new int[3]{1, 0, 2});
    std::cout << "  goluri[2] = " << goluri[2] << "\n";

    std::cout << "end of demo, p3 and s1 are destroyed:\n";
}
