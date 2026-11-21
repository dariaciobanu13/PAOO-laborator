#ifndef ITEM12_COPIERE_COMPLETA_HPP
#define ITEM12_COPIERE_COMPLETA_HPP

// Item 12: copy all parts of an object
// a Capitan is a Jucator, copying it must copy the Jucator part too

#include <string>

class Jucator {
private:
    std::string nume_;
    int numar_;

public:
    Jucator(const std::string& nume = "necunoscut", int numar = 0);
    Jucator(const Jucator& rhs);
    Jucator& operator=(const Jucator& rhs);
    virtual ~Jucator() = default;

    virtual void afiseaza() const;
};

class Capitan : public Jucator {
private:
    int aniCapitan_;
    std::string banderola_;   // a member added later: both copy functions must be updated

public:
    Capitan(const std::string& nume, int numar, int aniCapitan, const std::string& banderola);
    Capitan(const Capitan& rhs);
    Capitan& operator=(const Capitan& rhs);

    void afiseaza() const override;
};

void demoItem12();

#endif
