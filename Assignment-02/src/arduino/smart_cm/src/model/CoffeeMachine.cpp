#include "CoffeeMachine.h"
#include "config.h"

ProductType::ProductType(const String& name, int num){
  this->name = name;
  this->numProducts = num;
}

const String& ProductType::getName(){
    return name;
}

int ProductType::getNumProducts(){
    return numProducts;
}

void ProductType::consumeProduct(){
    numProducts--;
}

CoffeeMachine::CoffeeMachine(){
    currentSelection = -1;
}

void CoffeeMachine::init(){
    refill();
    reset();
}

void CoffeeMachine::nextSelection(){
    bool found = false;
    int count = 0;
    while (!found && count < nTypesOfItems){
        currentSelection = (currentSelection + 1) % nTypesOfItems;
        if (products[currentSelection]->getNumProducts() > 0){
            found = true;
        } else {
            count++;            
        }
    }
    if (!found){
        assistance = true;
        idle = false;
    }
}

void CoffeeMachine::prevSelection(){
    bool found = false;
    int count = 0;
    while (!found && count < nTypesOfItems){
        currentSelection--;
        if (currentSelection < 0) {
            currentSelection = nTypesOfItems - 1;
        } 
        if (products[currentSelection]->getNumProducts() > 0){
            found = true;
        } else {
            count++;            
        }
    }
    if (!found){
        assistance = true;
        idle = false;
    }
}

int CoffeeMachine::getNumberAvailableItems(){
    int countProds = 0;
    for (int i = 0; i < nTypesOfItems; i++){
        countProds += products[i]->getNumProducts();
    }
    return countProds;
}


ProductType* CoffeeMachine::getCurrentSelectedProduct(){
    return products[currentSelection];
}

void CoffeeMachine::addProductType(const String& name, int num){
    products[nTypesOfItems++] = new ProductType(name, num);
}

void CoffeeMachine::startMakingSelectedProduct(){
    if (!assistance) {
        products[currentSelection]->consumeProduct();
        isMaking = true;
        isProdReady = false;
        idle = false;
    }
}

bool CoffeeMachine::isMakingProduct(){
    return isMaking;
}

bool CoffeeMachine::isProductReady(){
    return isProdReady;
}

void CoffeeMachine::notifyProductReady(){
    isMaking = false;
    isProdReady = true;
}

void CoffeeMachine::removeProduct(){
    isProdReady = false;
    
    int countProds = getNumberAvailableItems();
    if (countProds > 0){
        idle = true;
        if (products[currentSelection]->getNumProducts() == 0){
            this->nextSelection();
        }
    } else {
        assistance = true;
    }
}

bool CoffeeMachine::isProductRemoved() {
    return (isProdReady == false); 
}

bool CoffeeMachine::updateSugarLevel(int level){
    int prev = sugarLevel;
    sugarLevel = level;
    return prev != sugarLevel;
}

int CoffeeMachine::getSugarLevel(){
    return sugarLevel;
}

bool CoffeeMachine::isIdle(){
    return idle;
}

bool CoffeeMachine::needsAssistance(){
    return assistance;
}

void CoffeeMachine::startSelfTest(){
    selfTestOngoing = true;
    idle = false;
    numSelfTests++;
}

bool CoffeeMachine::isDoingSelfTest(){
    return selfTestOngoing;
}

void CoffeeMachine::selfTestCompleted(bool assistanceReq){
    selfTestOngoing = false;
    if (assistanceReq){
        assistance = true;
        idle = false;
    } else {
        assistance = false;
        idle = true;
    }
}

void CoffeeMachine::reset(){
    currentSelection = 0;
    isMaking = false;
    idle = true;
    assistance = false;
    selfTestOngoing = false;
    numSelfTests = 0;
}

int CoffeeMachine::getNumSelfTests(){
    return numSelfTests;
}

void CoffeeMachine::refill(){
    nTypesOfItems = 0;
    addProductType("Coffee", N_ITEMS_COFFEE);
    addProductType("Tea", N_ITEMS_TEA);
    addProductType("Chocolate", N_ITEMS_CHOCOLATE);
    currentSelection = 0;
}

void CoffeeMachine::recover(){
    isMaking = false;
    idle = true;
    assistance = false;
    selfTestOngoing = false;
}