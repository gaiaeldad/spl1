#include "SelectionPolicy.h"
#include <vector>
#include <stdexcept>
using std::vector;
#include <climits>


//Naive Selection 
NaiveSelection:: NaiveSelection(): lastSelectedIndex(-1){

}
const FacilityType& NaiveSelection::selectFacility(const vector <FacilityType>& facilitiesOptions){
    if (facilitiesOptions.empty()) {
        throw std::invalid_argument("facilitiesOptions is empty");
    }
    
lastSelectedIndex = (lastSelectedIndex + 1) % facilitiesOptions.size();
return facilitiesOptions[lastSelectedIndex];

}
const string NaiveSelection::toString(){
    return "Last selected index is:" + std::to_string(lastSelectedIndex);
}

NaiveSelection* NaiveSelection:: clone() const override{ ///do need to see how we delet this in all the clones in this class 
    return new NaiveSelection(*this);
}

NaiveSelection::~NaiveSelection() override = default; 


//need to wrtie the balnced 
 BalancedSelection:: BalancedSelection(int LifeQualityScore, int EconomyScore, int EnvironmentScore):
 LifeQualityScore(LifeQualityScore), EconomyScore(EconomyScore), EnvironmentScore(EnvironmentScore){
 }

const FacilityType& BalancedSelection:: selectFacility(const vector<FacilityType>& facilitiesOptions) override{
    if (facilitiesOptions.empty()) {
        throw std::invalid_argument("facilitiesOptions is empty");}
    int min = INT_MAX;
    FacilityType* selectedFacility = nullptr;
    for (FacilityType &cand : facilitiesOptions){
         int temp = findDiff(cand);
        if( temp < min){
            min = temp;
            selectedFacility = &cand;
        }
    }
    return *selectedFacility; //return * or &
}

int BalanceSelection:: findDiff(const FacilityType& FacilityCand){
    int SumLifeQualityScore = this->LifeQualityScore + FacilityCand.getLifeQualityScore();
    int SumEconomyScore = this->EconomyScore + FacilityCand.getEconomyScore();
    int SumEnvironmentScore = this->EnvironmentScore + FacilityCand.getEnvironmentScore();
    int maxScore = std::max({SumLifeQualityScore, SumEconomyScore, SumEnvironmentScore});
    int minScore = std::min({SumLifeQualityScore, SumEconomyScore, SumEnvironmentScore});
    return  maxScore - minScore;
}

const string BalanceSelection::toString(){
    return "The LifeQuality score is " + std::to_string(LifeQualityScore) +
     ", The Economy score is " + std::to_string(EconomyScore) +
      ", The Environment score is " + std::to_string(EnvironmentScore);}

BalanceSelection* BalanceSelection:: clone() const override{ 
    return new BalanceSelection(*this);
}

BalanceSelection::~BalanceSelection() = default; 

void BalancedSelection ::setScores(int Curr_Life, int Curr_Econmy, int Curr_Env){/// צריכה קבל גם מה שבבניה
    LifeQualityScore = Curr_Life;
    EconomyScore =  Curr_Econmy;
    EnvironmentScore = Curr_Env;
}


// EconomySelection 
EconomySelection:: EconomySelection(): lastSelectedIndex(-1){}

const FacilityType& EconomySelection:: selectFacility(const vector<FacilityType>& facilitiesOptions) override{
    if (facilitiesOptions.empty()) {
        throw std::invalid_argument("facilitiesOptions is empty");
    }
    
    int size = facilitiesOptions.size();
    int currentIndex = (lastSelectedIndex + 1) % size; 

    for (int i = 0; i < size; ++i) {
        if (facilitiesOptions[currentIndex].getCategory() == FacilityCategory::ECONOMY) {
            lastSelectedIndex = currentIndex; 
            return facilitiesOptions[currentIndex];
        }
        currentIndex = (currentIndex + 1) % size; 
    }

    // If no ECONOMY facility is found, throw an exception
    throw std::runtime_error("No facility with ECONOMY category found");
}

const string EconomySelection::toString(){
    return "Last selected index is:" + std::to_string(lastSelectedIndex);
}

EconomySelection* EconomySelection:: clone() const override{ 
    return new EconomySelection(*this);
}

EconomySelection::~EconomySelection() = default; 
    

// SustainabilitySelection 
SustainabilitySelection:: SustainabilitySelection(): lastSelectedIndex(-1){}

const FacilityType& SustainabilitySelection:: selectFacility(const vector<FacilityType>& facilitiesOptions) override{
    if (facilitiesOptions.empty()) {
        throw std::invalid_argument("facilitiesOptions is empty");
    }
    
    int size = facilitiesOptions.size();
    int currentIndex = (lastSelectedIndex + 1) % size; 

    for (int i = 0; i < size; ++i) {
        if (facilitiesOptions[currentIndex].getCategory() == FacilityCategory::ENVIRONMENT) {
            lastSelectedIndex = currentIndex; 
            return facilitiesOptions[currentIndex];
        }
        currentIndex = (currentIndex + 1) % size; 
    }

    // If no ENVIRONMENT facility is found, throw an exception
    throw std::runtime_error("No facility with ENVIRONMENT category found");
}

const string SustainabilitySelection::toString(){
    return "Last selected index is:" + std::to_string(lastSelectedIndex);
}

SustainabilitySelection* SustainabilitySelection:: clone() const override{ 
    return new SustainabilitySelection(*this);
}

SustainabilitySelection::~SustainabilitySelection() = default; 
    


