#ifndef ITEM6_INTERZICERE_COPIERE_HPP
#define ITEM6_INTERZICERE_COPIERE_HPP

// Item 6: explicitly disallow the use of compiler generated functions you do not want
// a stadium is unique, a second copy of it makes no sense

#include <string>

// C++98: private and never defined
// outside code -> compile error, members and friends -> link error
class Stadion98 {
private:
    std::string nume_;

    Stadion98(const Stadion98&);
    Stadion98& operator=(const Stadion98&);

    friend void copiazaPrinFriend(const Stadion98& stadion);

public:
    explicit Stadion98(const std::string& nume);
    const std::string& getNume() const;
};

// C++98, reusable: the generated copy functions of the derived class
// need these, and they can't reach them
class Uncopyable {
protected:
    Uncopyable() {}
    ~Uncopyable() {}

private:
    Uncopyable(const Uncopyable&);
    Uncopyable& operator=(const Uncopyable&);
};

class StadionUncopyable : private Uncopyable {
private:
    std::string nume_;

public:
    explicit StadionUncopyable(const std::string& nume);
    const std::string& getNume() const;
};

// C++11: public, so the error says "deleted", not "private"
// always caught at compile time, even for members and friends
class StadionModern {
private:
    std::string nume_;

public:
    explicit StadionModern(const std::string& nume);

    StadionModern(const StadionModern&) = delete;
    StadionModern& operator=(const StadionModern&) = delete;

    const std::string& getNume() const;
};

void demoItem6();

#endif
