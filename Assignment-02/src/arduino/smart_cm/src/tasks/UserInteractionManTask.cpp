#include "tasks/UserInteractionManTask.h"
#include "Arduino.h"
#include "kernel/Logger.h"
#include "config.h"

UserInteractionManTask::UserInteractionManTask(UserConsole* pConsole, CoffeeMachine* pCM): 
    pConsole(pConsole), pCoffeeMachine(pCM) {
    setState(BOOTING);
}
  
void UserInteractionManTask::tick(){
    pConsole->sync();
    long currentTime = millis();

    switch (state){
    case BOOTING: {
            pConsole->init();
            pCoffeeMachine->init();
            setState(WELCOME);
        break;
    }
    case WELCOME: {
        if (justEnteredInState()){
            pConsole->showWelcome();
        }  
        
        if (elapsedTimeInState() > 1000){
            setState(READY);
        }        
    }
    case READY: {
        if (justEnteredInState()){
            pConsole->showReady();
            pConsole->notifyNumItems(pCoffeeMachine->getNumberAvailableItems());
            pConsole->notifyNumSelfTests(pCoffeeMachine->getNumSelfTests());
            itemSelected = false;
            lastTimeDetectedPres = currentTime;
        }   
        
        if (pConsole->detectedPresence()){
            lastTimeDetectedPres = currentTime;
        }

        if (pCoffeeMachine->needsAssistance()){
            setState(NEED_ASSISTANCE);  
        } else if (!pCoffeeMachine->isDoingSelfTest()){
            
            if (currentTime - lastTimeDetectedPres > T_IDLE){
                setState(SLEEPING);
            } else {
                bool changed = pCoffeeMachine->updateSugarLevel(pConsole->getSugarLevel());
                if (changed){
                    Logger.log("sugar updated ");
                    pConsole->showUpdatedSugarLevel(pCoffeeMachine->getSugarLevel());
                }

                if (pConsole->isUpPressed()){
                    pCoffeeMachine->nextSelection();
                    pConsole->showItem(pCoffeeMachine->getCurrentSelectedProduct());  
                    itemSelected = true;
                    itemSelectionTime = currentTime;
                    lastTimeDetectedPres = currentTime;
                } else if (pConsole->isDownPressed()){
                    pCoffeeMachine->prevSelection();
                    pConsole->showItem(pCoffeeMachine->getCurrentSelectedProduct());  
                    itemSelected = true;
                    lastTimeDetectedPres = currentTime;
                    itemSelectionTime = currentTime;
                } else if (pConsole->isMakePressed()){
                    pCoffeeMachine->startMakingSelectedProduct();
                    setState(MAKING);
                }   

                if (itemSelected && (currentTime - itemSelectionTime > T_ITEM_DISPLAYED)){
                    pConsole->showReady();
                    itemSelected = false;
                }
            }
        } else {
            setState(DOING_SELF_TEST);
        }
        break;
    }
    
    case MAKING: {        
        if (justEnteredInState()){
            pConsole->showMaking(pCoffeeMachine->getCurrentSelectedProduct());
            pConsole->notifyNumItems(pCoffeeMachine->getNumberAvailableItems());
        }        
        if (pCoffeeMachine->isProductReady()){
            pConsole->showProductReady(pCoffeeMachine->getCurrentSelectedProduct());
            setState(PRODUCT_READY);
        }
        break;
    } 
    
    case PRODUCT_READY: {
        if (pCoffeeMachine->isProductRemoved()){
            setState(READY);
        } else if (pCoffeeMachine->needsAssistance()){
            setState(NEED_ASSISTANCE);
        }
        break;
    }

    case DOING_SELF_TEST: {
        if (justEnteredInState()){
           pConsole->showSelfTest();
           pConsole->notifyNumSelfTests(pCoffeeMachine->getNumSelfTests());
        }
        if (pCoffeeMachine->isIdle()){
            setState(READY);
        } else if (pCoffeeMachine->needsAssistance()){
            setState(NEED_ASSISTANCE);  
        }   
        break;
    }

    case NEED_ASSISTANCE: {
        if (justEnteredInState()){
            if (pCoffeeMachine->getNumberAvailableItems() == 0){
                pConsole->showNeedAssistanceNoMoreItems();         
            } else {
                pConsole->showNeedAssistanceFailedSelfTest();         
            } 
        }   
        bool toRefill;
        bool toRecover;
        bool present = pConsole->checkCmd(toRefill, toRecover);
        if (present){
            if (toRefill){
                pCoffeeMachine->refill();        
                pCoffeeMachine->recover();
                setState(READY);
            } else if (toRecover){
                pCoffeeMachine->recover();
                setState(READY);
            }
        }
        break;
    }

    case SLEEPING:
        Logger.log("time to sleep");
        pConsole->sleep();
        Logger.log("back");
        setState(READY);
        lastTimeDetectedPres = currentTime;
        break;
  }
}

void UserInteractionManTask::setState(int s){
    state = s;
    stateTimestamp = millis();
    isJustEnteredInState = true;
}

long UserInteractionManTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

bool UserInteractionManTask::justEnteredInState(){
    if (isJustEnteredInState){
        isJustEnteredInState = false;
        return true;
    } else {
        return false;
    }
}

