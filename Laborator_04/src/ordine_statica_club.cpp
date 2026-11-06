#include "clase_gresite.hpp"
#include "item4_initializare.hpp"

extern Liga ligaGlobala;

// runs before main, and ordine_statica_liga.cpp is linked after this file,
// so ligaGlobala is still zero here: 0 - 1 = -1 opponents
static const int adversari = ligaGlobala.getNrEchipe() - 1;

int adversariFiasco()
{
    return adversari;
}
