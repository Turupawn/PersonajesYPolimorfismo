#include "guerrero.h"

Guerrero::Guerrero(int vida, int ataque)
{
    this->vida = vida;
    this->ataque = ataque;
    this->tipo = "Guerrero";

}

void Guerrero::SpecialPower()
{
    ataque*=2;
    vida/=2;
}

void Guerrero::atacar(Personaje*atacado)
{
    atacado->vida-=this->ataque;
}
