
#ifndef GUERRERO_H
#define GUERRERO_H
#include "Personaje.h"
#include <iostream>
using namespace std;
class Guerrero : public Personaje{

public:
    Guerrero(int vida, int ataque);
    void SpecialPower();
    void atacar(Personaje*atacado);
};

#endif
