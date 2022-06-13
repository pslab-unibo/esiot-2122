#include "tasks/RemoveProductTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"

#define REMOVAL_DISTANCE 0.40

RemoveProductTask::RemoveProductTask(CoffeeMachine* pCM): 
    pCoffeeMachine(pCM) {
    pSonar = new Sonar(SONAR_ECHO_PIN, SONAR_TRIG_PIN, 10000);
    setState(IDLE);
}
  
void RemoveProductTask::tick(){
    switch (state){    
    case IDLE: {
        if (pCoffeeMachine->isProductReady()){
            setState(REMOVING);
        }
        break;
    }
    case REMOVING: {
        float distance = pSonar->getDistance();
        if (distance != NO_OBJ_DETECTED && distance < REMOVAL_DISTANCE){
            Logger.log("removal: removed");
            pCoffeeMachine->removeProduct();       
            setState(IDLE);
        } else if (elapsedTimeInState() > T_TIMEOUT){
            Logger.log("removal: timeout");
            pCoffeeMachine->removeProduct();       
            setState(IDLE);
        }
        break;
    }}
}

void RemoveProductTask::test(){
}


void RemoveProductTask::setState(int s){
    state = s;
    stateTimestamp = millis();
}

long RemoveProductTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}
