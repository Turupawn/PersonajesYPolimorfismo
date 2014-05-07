#include "Arquero.h"

Arquero::Arquero(int vida, int ataque)
{
    this->vida = vida;
    this->ataque = ataque;
    this->tipo = "Arquero";
    this->super_flechas = 0;
}

void Arquero::print(){
    cout<<tipo<<endl;
    cout<<"vida :"<<vida<<endl;
    cout<<"ataque: "<<ataque<<endl;
    cout<<"super flechas: "<<super_flechas<<endl;

}

void Arquero::SpecialPower(){
    this->super_flechas+=5;

}

Arquero::~Arquero()
{
    //dtor
}

void Arquero::atacar(Personaje*atacado)
{
    atacado->vida-=super_flechas*ataque;
    super_flechas=0;
}
