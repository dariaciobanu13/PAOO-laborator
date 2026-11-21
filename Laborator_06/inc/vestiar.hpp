#ifndef VESTIAR_HPP
#define VESTIAR_HPP

// a resource that is not memory (Mutex in the book)
// with a C style API: lock and unlock by pointer

#include <string>

struct Vestiar {
    std::string echipa;
    bool incuiat = false;
};

void incuie(Vestiar* v);
void descuie(Vestiar* v);   // prints an error if it is already unlocked

#endif
