#ifndef ECHIPA_H
#define ECHIPA_H

#include <cstddef>
#include <string>

class Echipa {
private:
    const std::string nume;   // const, so it can only be set in the init list
    std::string* jucatori;    // players array, allocated on the heap
    std::size_t nrJucatori;
    std::size_t capacitate;

public:
    Echipa(const std::string& numeEchipa, std::size_t cap);
    ~Echipa();

    Echipa(const Echipa& other);        // copy constructor
    Echipa(Echipa&& other) noexcept;    // move constructor

    // no assignment, otherwise a = b would only copy the pointer
    Echipa& operator=(const Echipa&) = delete;
    Echipa& operator=(Echipa&&) = delete;

    bool adaugaJucator(const std::string& jucator);
    void schimbaJucator(std::size_t index, const std::string& jucatorNou);

    const std::string& getNume() const;
    std::size_t getNrJucatori() const;
    void afiseaza() const;
};

#endif
