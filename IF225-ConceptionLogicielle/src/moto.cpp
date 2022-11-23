#include "moto.h"

Moto::Moto(const std::string & immatricul, int cylindree) :
    Vehicule(immatricul),
    cylindree(cylindree)

{

}

std::string Moto::getImmatriculation(void){
    return immatriculation;
}

int Moto::getCylindree(void){
    return cylindree;
}