#ifndef MOTO_H
#define MOTO_H

#include "vehicule.h"

class Moto : public Vehicule
{ 
public: 
    Moto(const std::string & immatricul, int cylindree);
    std::string getImmatriculation(void);
    int getCylindree(void);

private : 
    int cylindree;
};

    #endif

