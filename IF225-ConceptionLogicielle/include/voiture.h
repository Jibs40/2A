#ifndef VOITURE_H
#define VOITURE_H


#include "vehicule.h"

class Voiture : public Vehicule
{ 
public: 
    Voiture(const std::string & immatricul, int nombredeportes);
    std::string retourneImmatriculation(Voiture v);

private : 
    int nbportes;
};

#endif