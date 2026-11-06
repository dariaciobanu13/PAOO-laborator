#ifndef ITEM5_FUNCTII_GENERATE_HPP
#define ITEM5_FUNCTII_GENERATE_HPP

// Item 5: know what functions C++ silently writes and calls

#include "logger_functii.hpp"

#include <string>

// nothing special declared, the compiler writes everything
class Scor {
private:
    LoggerFunctii echipa_;
    int goluri_ = 0;

public:
    int getGoluri() const;
};

// has a constructor of its own, so no default constructor is generated
class Arbitru {
private:
    std::string nume_;

public:
    explicit Arbitru(const std::string& nume);
    const std::string& getNume() const;
};

// a reference can't be rebound and a const can't change,
// so the compiler refuses to write operator=
class Transfer {
private:
    std::string& club_;
    const int suma_;

public:
    Transfer(std::string& club, int suma);
    void afiseaza() const;
};

// operator= is private in the base, so the derived class can't get one
class BazaFaraAtribuire {
public:
    BazaFaraAtribuire() = default;

private:
    BazaFaraAtribuire& operator=(const BazaFaraAtribuire&);
};

class Rezerva : public BazaFaraAtribuire {
};

// owns heap memory, so the generated copies would be wrong
// bad version: AntrenorShallow in clase_gresite.hpp
class Antrenor {
private:
    std::string* nume_;

public:
    explicit Antrenor(const std::string& nume);
    Antrenor(const Antrenor& other);
    Antrenor& operator=(const Antrenor& other);
    ~Antrenor();

    void schimbaNume(const std::string& nume);
    void afiseaza() const;
};

void demoItem5();

#endif
