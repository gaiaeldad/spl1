#include "Plan.h"


 Plan:: Plan(const int planId, const Settlement &settlement, SelectionPolicy *selectionPolicy, const vector<FacilityType> &facilityOptions)
 :plan_id(planId), settlement(&settlement), SelectionPolicy(selectionPolicy),status(PlanStatus: AVALIABLE),facilityOptions(facilityOptions),
 life_quality_score(0), economy_score(0), environment_score(0){}

 const int Plan:: getlifeQualityScore() const{
    return life_quality_score;
 }
const int Plan:: getEconomyScore() const{
    return economy_score;

}
const int  Plan:: getEnvironmentScore() const{
    return environment_score;
}  

void Plan::setSelectionPolicy(SelectionPolicy *selectionPolicy){
    this->SelectionPolicy = selectionPolicy;
}   

void Plan::step(){//need to check that this is correct and that we have all steps 
    while ( status == PlanStatus::AVALIABLE){
        if (dynamic_cast<BalancedSelection*>(this->selectionPolicy) != nullptr){
            this->selectionPolicy->setScores(life_quality_score, economy_score, environment_score);
        }
     FacilityType &buildThis = this->selectionPolicy->selectFacility(&facilityOptions);
     underConstruction.push_back(Facility( buildThis, this->Settlement->getname()));//should we write new before facility?
        
        if(underConstruction.size() == this->settlement->getLimit()){
             this->status = PlanStatus::BUSY;
         }
    }
    for ( iter = underConstruction.begin(); iter != underConstruction.end();) {
    FacilityStatus nowstatus = (*iter)->step();
    if (nowstatus == FacilityStatus::OPERATIONAL) {
        facilities.push_back(*iter);
        scoreUpdate(*iter); 
        iter = underConstruction.erase(iter);
    } else {
        ++iter;
    }
}


//this is what i wrote 
    for (Facility F: underConstruction){// write this in iterator so i can erase later 
         FacilityStatus nowstatus = F->step();
        if (nowstatus = FacilityStatus::OPERATIONAL){
            facilities.push_back(*F);
             underConstruction.erase(*F);
             Plan::scoreUpdate(*F);
        }
    }
    if (underConstruction.size() < this->settlement->getLimit()){
        this->status = PlanStatus::AVALIABLE;
     }
  }
         
    


//need to see what we want here 
void Plan::scoreUpdate(Facility* facility){
    this->life_quality_score += facility->getLifeQualityScore();
    this->economy_score += facility->getEconomyScore();
    this->environment_score += facility->getEnvironmentScore();
}





 void Plan::printStatus(){
  if (status == PlanStatus::AVALIABLE) {
    cout << "plan id: " << plan_id << "settlement: " << settlement <<  "Status: Available" << endl;
} else {
    cout << "Status: Busy" << endl;
}
 }
// we need to decide what we want to print out 

const vector<Facility*>& Plan::getFacilities() const{
       return facilities;
}

void  Plan::addFacility(Facility* facility){
    facilities.push_back(facility);
}
          
    string Plan::toString() const {
    string ans = "PlanID: " + std::to_string(plan_id) + "\n";
    ans += "SettlementName: " + settlement->getName() + "\n"; 
    ans += "PlanStatus: " + (status == PlanStatus::AVALIABLE ? "AVALIABLE" : "BUSY") + "\n";
    ans += "SelectionPolicy: " + selectionPolicy->toString() + "\n"; 
    ans += "LifeQualityScore: " + std::to_string(life_quality_score) + "\n";
    ans += "EconomyScore: " + std::to_string(economy_score) + "\n";
    ans += "EnvironmentScore: " + std::to_string(environment_score) + "\n";

    // Print  The Facility details
    for (const Facility* facility: facilities) {
        ans += "FacilityName: " + facility->toString() + "\n";  
        ans += "FacilityStatus: " + (facility->getStatus() == FacilityStatus::UNDER_CONSTRUCTION ? "UNDER_CONSTRUCTION" : "OPERATIONAL") + "\n"; 
    }

    return ans;
        }        


//make sure the rule of 5 is implemented 