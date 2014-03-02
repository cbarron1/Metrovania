#include "CEntity.h"
 
std::vector<CEntityCol> CEntityCol::EntityColList;
//simple class that contains 2 entitys that have collided with each other
CEntityCol::CEntityCol() {
    this->EntityA = NULL;
    this->EntityB = NULL;
}
