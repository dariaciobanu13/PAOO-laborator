#ifndef ITEM10_RETURN_THIS_HPP
#define ITEM10_RETURN_THIS_HPP

// Item 10: have assignment operators return a reference to *this
// so a = b = c works for our class like it does for int

class Scor {
private:
    int gazde_;
    int oaspeti_;

public:
    Scor(int gazde = 0, int oaspeti = 0);
    Scor(const Scor&) = default;        // Item 5: we wrote operator=, so say we still want the copy ctor

    Scor& operator=(const Scor& rhs);   // copy assignment
    Scor& operator+=(const Scor& rhs);  // compound assignment, same rule
    Scor& operator=(int goluri);        // assignment from another type, same rule

    void afiseaza(const char* eticheta) const;
};

void demoItem10();

#endif
