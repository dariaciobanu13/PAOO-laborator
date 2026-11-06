// each block is built by its own target and must fail, see CMakeLists.txt

#include "item4_initializare.hpp"
#include "item5_functii_generate.hpp"
#include "item6_interzicere_copiere.hpp"

#include <string>

#if defined(CONST_IN_CORP)
// item 4: a const member can't be assigned in the constructor body
class Gresit {
private:
    const int id_;

public:
    explicit Gresit(int id)
    {
        id_ = id;
    }
};
#endif

#if defined(LINK_FRIEND)
// item 6: compiles because a friend can reach the private copy constructor,
// but that constructor was never defined, so the linker fails
void copiazaPrinFriend(const Stadion98& stadion)
{
    Stadion98 copie(stadion);
}
#endif

int main()
{
#if defined(ATRIBUIRE_REFERINTA)
    // item 5: operator= was not generated
    std::string club1 = "Rapid";
    std::string club2 = "Dinamo";
    Transfer a(club1, 100);
    Transfer b(club2, 200);
    a = b;
#elif defined(COPIE_PRIVATA)
    // item 6: the copy constructor is private
    Stadion98 a("Arena Nationala");
    Stadion98 b(a);
#elif defined(COPIE_UNCOPYABLE)
    // item 6: the generated copy constructor can't reach the one from Uncopyable
    StadionUncopyable a("Dan Paltinisanu");
    StadionUncopyable b(a);
#elif defined(COPIE_DELETE)
    // item 6: the copy constructor is deleted
    StadionModern a("Ghencea");
    StadionModern b(a);
#elif defined(LINK_FRIEND)
    Stadion98 a("Arena Nationala");
    copiazaPrinFriend(a);
#endif
    return 0;
}
