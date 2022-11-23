#ifndef CAMION_H
#define CAMION_H

#include "vehicule.h"

class Camion : public Vehicule
{ 
public: 
    Camion(const std::string & immatricul, int masse,int hauteur);
private : 
    int weigth;
    int heigth;
};

#endif