#ifndef GARAGE_H
#define GARAGE_H

#include "camion.h"
#include "camionCiterne.h"
#include "voiture.h"
#include "vehicule.h"
#include "moto.h"

#include <vector>
#include <map>

using std::map;

class Garage 
{
    public : 
        Garage(void);
        void addTruck(Camion c);
        int getTruck(void);
        void addCar(Voiture v);
        Voiture getCar(std::string immatriculation);
        void afficheTaille(void);

    private :
        std::vector<Camion> v;
        std::map<std::string,Voiture> m;


};


#endif
