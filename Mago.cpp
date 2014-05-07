#include "Mago.h"

Mago::Mago(int vida, int ataque)
{
    this->vida = vida;
    this->ataque = ataque;
    this->tipo = "Mago";
    this->super_rayo = false;



}

void Mago::SpecialPower(){
    super_rayo = true;



}

void Mago::print(){
    cout<<tipo<<endl;
    cout<<"vida :"<<vida<<endl;
    cout<<"ataque: "<<ataque<<endl;
    cout<<"super rayo: "<<super_rayo<<endl;
}

Mago::~Mago()
{
    cout<<"Destructor"<<endl;

}

void Mago::atacar(Personaje*atacado)
{
    if(super_rayo)
    {
        atacado->vida-=this->ataque*2;
        super_rayo=false;
    }
    else
    {
        atacado->vida-=this->ataque;
    }
}
