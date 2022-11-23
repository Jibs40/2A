#include <iostream>
#include "garage.h"
#include <vector>


Garage::Garage(void){

}

void Garage::addTruck(Camion c){
    v.push_back(c);
    std::cout << "Camion ajouté :" + c.immatriculation
                << std::endl;
}

int Garage::getTruck(void){
    return 0;
}

void Garage::addCar(Voiture v){
    m.insert({v.retourneImmatriculation(v),v});
    std::cout << "Voiture ajouté :" + v.retourneImmatriculation(v)
                << std::endl;
}

Voiture Garage::getCar(std::string immatriculation){
    std::cout<<"Voiture ressortie :" + m.find(immatriculation)->first 
                << std::endl;
    return m.find(immatriculation)->second;
}

void Garage::afficheTaille(){
    std::cout<<"Le garage contient : ",
    std::cout<<v.size(),
    std::cout<<" vehicules.",
    std::cout<<std::endl;
}