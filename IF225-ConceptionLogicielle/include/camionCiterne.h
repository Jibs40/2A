#ifndef CAMIONCITERNE_H
#define CAMIONCITERNE_H

#include "camion.h"

class CamionCiterne : public Camion
{ 
public: 
    CamionCiterne(const std::string & immatricul, int contenance);
    int getContenance(void);

private : 
    int contenance;
};

#endif