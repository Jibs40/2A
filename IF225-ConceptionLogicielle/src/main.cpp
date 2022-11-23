#include <iostream>

#include "garage.h"

int main(int argc, char const *argv[]){
Garage garage;
Moto motoThomas            = Moto("AA-JW-40",650); 
CamionCiterne domitille    = CamionCiterne("DomiDu33",1000);
Camion pouetpouet          = Camion("Pouetpouet",1000,2);
Voiture ouioui             = Voiture("AQ-WWW-40",3);

garage.addTruck(pouetpouet);
garage.addCar(ouioui);
garage.getCar("AQ-WWW-40");
garage.afficheTaille();
std::cout   << motoThomas.getCylindree()
            << std::endl
            << motoThomas.getImmatriculation()
            << std::endl
            << "Contenance Domitille" << domitille.getContenance()
            << std::endl;            
}
