#ifndef __CM__
#define __CM__

#include <Arduino.h>

#define MAX_NUM_TYPES 5

class ProductType {

public:
    ProductType(const String& name, int num);

    const String& getName();
    int getNumProducts();
    void consumeProduct();

private:
    String name;
    int numProducts;
};

class CoffeeMachine {
    
public: 
    CoffeeMachine();

    void init();
    void nextSelection();
    void prevSelection();

    ProductType* getCurrentSelectedProduct();
    bool updateSugarLevel(int level);
    int getSugarLevel();

    void startMakingSelectedProduct();
    bool isIdle();
    bool isMakingProduct();
    bool isProductReady();
    void notifyProductReady();
    void removeProduct();
    bool isProductRemoved();
    void startSelfTest();
    bool isDoingSelfTest();
    void selfTestCompleted(bool assistance);
    
    bool needsAssistance();
    int getNumberAvailableItems();
    int getNumSelfTests();
    void refill();
    void recover();
    
    void reset();

private:

    void addProductType(const String& name, int num);

    bool idle;
    bool assistance;
    bool isMaking;
    bool isProdReady;
    bool selfTestOngoing;

    int sugarLevel;

    int currentSelection;
    int nTypesOfItems;
    ProductType* products[MAX_NUM_TYPES];

    int numSelfTests;
};


#endif