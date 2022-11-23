#include "camionCiterne.h"

CamionCiterne::CamionCiterne(const std::string & immatricul, int contenance):
Camion(immatricul,3,4),
contenance(contenance)
{

}

int CamionCiterne::getContenance(void){
    return contenance;
}
