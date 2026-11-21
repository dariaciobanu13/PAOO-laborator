#ifndef CONTRACT_HPP
#define CONTRACT_HPP

// the resource for Item 13 (Investment in the book)
// counts how many contracts are alive, so a leak is visible

#include <string>

class Contract {
private:
    std::string jucator_;
    int salariu_;
    static int inViata_;

public:
    Contract(const std::string& jucator, int salariu);
    ~Contract();

    void semneaza() const;
    static int inViata();
};

// factory: returns a heap object, the caller must delete it
Contract* creeazaContract(const std::string& jucator, int salariu);

#endif
