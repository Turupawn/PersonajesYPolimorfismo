#ifndef ARQUERO_H
#define ARQUERO_H

#include "Personaje.h"
class Arquero : public Personaje
{
    public:
        int super_flechas;
        Arquero(int vida, int ataque);

        void print();
        void SpecialPower();
        void atacar(Personaje*atacado);


        virtual ~Arquero();
    protected:
    private:
};

#endif // ARQUERO_H
