#include "Settlement.h"


Settelment::Settlement(const string &name, SettlementType type)
:name(name), type(type){
switch (type){
        case SettlementType::VILLAGE: limit = 1; break;
        case SettlementType::CITY: limit = 2; break;
        case SettlementType::METROPOLIS: limit = 3;
    }
} 

 const string &Settlement::getName() const{
    return name;
 }

 SettlementType Settlement::getType() const{
    return type;
 }

 string SettlementTypeToString(SettlementType){
    switch (type){
        case SettlementType::VILLAGE: return "Village";
        case SettlementType::CITY: return "City";
        case SettlementType::METROPOLIS: return "Metropolis";
    }
 }

 const string Settlement::toString() const{
    return "Settlement:" + name + "Type:" + SettlementTypeToString(type);
 }

 const int Settlement::getLimit(){
   return limit;
 }