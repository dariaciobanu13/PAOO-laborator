#ifndef ITEM14_COPIERE_RAII_HPP
#define ITEM14_COPIERE_RAII_HPP

// Item 14: think carefully about copying behavior in resource-managing classes
// four answers to "what does copying a key mean?"

#include "vestiar.hpp"

#include <cstddef>
#include <memory>

// 1. prohibit copying: a copy of a lock makes no sense
class CheieUnica {
private:
    Vestiar* vestiar_;

public:
    explicit CheieUnica(Vestiar* v);
    ~CheieUnica();

    CheieUnica(const CheieUnica&) = delete;
    CheieUnica& operator=(const CheieUnica&) = delete;
};

// 2. reference counting: copies share the room, the last one unlocks it
// shared_ptr with a custom deleter: at count 0 it calls descuie, not delete
class CheieComuna {
private:
    std::shared_ptr<Vestiar> vestiar_;

public:
    explicit CheieComuna(Vestiar* v);
    long folositori() const;
    // no destructor, no copy functions: the generated ones do the right thing
};

// 3. deep copy: copy the resource too (like std::string), fits memory
class ListaJucatori {
private:
    int* numere_;
    std::size_t marime_;

public:
    ListaJucatori(std::size_t marime);
    ListaJucatori(const ListaJucatori& other);
    ListaJucatori& operator=(const ListaJucatori& rhs);
    ~ListaJucatori();

    void swap(ListaJucatori& other) noexcept;
    int& operator[](std::size_t i);
    void afiseaza(const char* eticheta) const;
};

// 4. transfer ownership: one owner, std::move hands the key over
class CheieTransferabila {
private:
    Vestiar* vestiar_;

public:
    explicit CheieTransferabila(Vestiar* v);
    ~CheieTransferabila();

    CheieTransferabila(const CheieTransferabila&) = delete;
    CheieTransferabila& operator=(const CheieTransferabila&) = delete;

    CheieTransferabila(CheieTransferabila&& other) noexcept;
    CheieTransferabila& operator=(CheieTransferabila&& rhs) noexcept;

    bool areVestiar() const;
};

void demoItem14();

#endif
