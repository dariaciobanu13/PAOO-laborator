#include "vestiar.hpp"

#include <iostream>

void incuie(Vestiar* v)
{
    if (v->incuiat)
        std::cout << "    !! " << v->echipa << " locker room is already locked\n";
    v->incuiat = true;
    std::cout << "    [locked " << v->echipa << "]\n";
}

void descuie(Vestiar* v)
{
    if (!v->incuiat)
        std::cout << "    !! ERROR: " << v->echipa << " locker room unlocked twice\n";
    v->incuiat = false;
    std::cout << "    [unlocked " << v->echipa << "]\n";
}
