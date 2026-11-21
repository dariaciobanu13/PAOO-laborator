#ifndef ITEM11_AUTOATRIBUIRE_HPP
#define ITEM11_AUTOATRIBUIRE_HPP

// Item 11: handle assignment to self in operator=
// every Echipa owns its logo on the heap (like Widget and Bitmap in the book)

#include <string>

class Sigla {
private:
    std::string desen_;

public:
    explicit Sigla(const std::string& desen);
    Sigla(const Sigla& other);   // prints, so we see when a copy is made
    const std::string& getDesen() const;
};

// solution 1: identity test, safe for a = a but not if new throws
class EchipaTestIdentitate {
private:
    std::string nume_;
    Sigla* sigla_;

public:
    EchipaTestIdentitate(const std::string& nume, const std::string& desen);
    EchipaTestIdentitate(const EchipaTestIdentitate& other);
    EchipaTestIdentitate& operator=(const EchipaTestIdentitate& rhs);
    ~EchipaTestIdentitate();
    void afiseaza() const;
};

// solution 2: careful ordering, copy first and delete after
class EchipaOrdine {
private:
    std::string nume_;
    Sigla* sigla_;

public:
    EchipaOrdine(const std::string& nume, const std::string& desen);
    EchipaOrdine(const EchipaOrdine& other);
    EchipaOrdine& operator=(const EchipaOrdine& rhs);
    ~EchipaOrdine();
    void afiseaza() const;
};

// solution 3: copy and swap, plus move assignment (C++11, slide 6)
class EchipaSwap {
private:
    std::string nume_;
    Sigla* sigla_;

public:
    EchipaSwap(const std::string& nume, const std::string& desen);
    EchipaSwap(const EchipaSwap& other);
    EchipaSwap& operator=(const EchipaSwap& rhs);
    EchipaSwap& operator=(EchipaSwap&& rhs) noexcept;
    ~EchipaSwap();

    void swap(EchipaSwap& other) noexcept;
    void afiseaza() const;
};

void demoItem11();

#endif
