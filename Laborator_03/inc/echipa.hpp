#ifndef ECHIPA_HPP
#define ECHIPA_HPP

#include <cstddef>
#include <string>

class Echipa {
private:
    const std::string nume_;   // const, so it can only be set in the init list
    std::string* jucatori_;    // players array, allocated on the heap
    std::size_t nrJucatori_;
    std::size_t capacitate_;

public:
    Echipa(const std::string& nume, std::size_t capacitate);
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
