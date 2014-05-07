

#include <iostream>
using namespace std;
#include "guerrero.h"
#include "Mago.h"
#include <vector>
#include "Arquero.h"

int main(){

    vector<Personaje*>personajes;
    personajes.push_back(new Mago(100,40));
    personajes.push_back(new Guerrero(150,60));
    personajes.push_back(new Arquero(100,10));


    for(int i = 0; i<personajes.size() ; i++)
    {
       personajes[i]->print();
    }

    cout<<"*** Ataques ***"<<endl;

    personajes[0]->atacar(personajes[1]);
    personajes[1]->atacar(personajes[2]);
    personajes[2]->atacar(personajes[0]);

    for(int i = 0; i<personajes.size() ; i++)
    {
       personajes[i]->print();
    }

    cout<<"*** Activo super poderes ***"<<endl;

    for(int i = 0; i<personajes.size() ; i++)
    {
        personajes[i]->SpecialPower();
    }

    for(int i = 0; i<personajes.size() ; i++)
    {
       personajes[i]->print();
    }

    cout<<"*** Ataques ***"<<endl;

    personajes[0]->atacar(personajes[1]);
    personajes[1]->atacar(personajes[2]);
    personajes[2]->atacar(personajes[0]);

    for(int i = 0; i<personajes.size() ; i++)
    {
        personajes[i]->print();
    }


//    Mago*m = new Mago();
//    delete m;

}
