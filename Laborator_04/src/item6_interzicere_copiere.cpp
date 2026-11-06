#include "item6_interzicere_copiere.hpp"
#include "afisare.hpp"

#include <iostream>
#include <type_traits>

Stadion98::Stadion98(const std::string& nume)
    : nume_(nume)
{
}

const std::string& Stadion98::getNume() const
{
    return nume_;
}

StadionUncopyable::StadionUncopyable(const std::string& nume)
    : nume_(nume)
{
}

const std::string& StadionUncopyable::getNume() const
{
    return nume_;
}

StadionModern::StadionModern(const std::string& nume)
    : nume_(nume)
{
}

const std::string& StadionModern::getNume() const
{
    return nume_;
}

template <typename T>
static void verificaCopiere(const T& stadion, const std::string& varianta)
{
    std::cout << "  " << varianta << " \"" << stadion.getNume() << "\": copy constructor? "
              << daNu(std::is_copy_constructible<T>::value) << ", operator=? "
              << daNu(std::is_copy_assignable<T>::value) << "\n";
}

void demoItem6()
{
    titlu("Item 6: forbidding copies");
    Stadion98 arena("Arena Nationala");
    StadionUncopyable bega("Dan Paltinisanu");
    StadionModern ghencea("Ghencea");

    verificaCopiere(arena, "C++98 private");
    verificaCopiere(bega, "C++98 Uncopyable");
    verificaCopiere(ghencea, "C++11 = delete");

    std::cout << "  deleting the copy also means no generated move: move constructor? "
              << daNu(std::is_move_constructible<StadionModern>::value) << "\n";
    std::cout << "  the real errors are in the eroare_copie_* and eroare_link_friend targets\n";
}
