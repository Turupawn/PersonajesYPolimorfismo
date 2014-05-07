#include "Personaje.h"

Personaje::Personaje()
{

}

Personaje::~Personaje()
{
    //dtor
}


void Personaje::print(){
    cout<<tipo<<endl;
    cout<<"vida: "<<vida<<endl;
    cout<<"ataque: "<<ataque<<endl;


}

string Personaje::getTipo()
{
    return tipo;
}
