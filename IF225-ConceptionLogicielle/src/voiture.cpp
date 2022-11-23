#include "voiture.h"

Voiture::Voiture(const std::string & immatricul,int nombredeportes)
        : Vehicule(immatricul),
        nbportes(nombredeportes)

{

}

std::string Voiture::retourneImmatriculation(Voiture v){
        return v.immatriculation;
}