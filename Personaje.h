#ifndef PERSONAJE_H
#define PERSONAJE_H

#include<iostream>
using namespace std;



class Personaje
{
    public:
        string tipo;
        int vida;
        int ataque;

        Personaje();
        virtual ~Personaje();
        virtual void SpecialPower() = 0;
        virtual void print();
        virtual void atacar(Personaje*atacado) = 0;
        string getTipo();
    protected:
    private:
};

#endif // PERSONAJE_H
