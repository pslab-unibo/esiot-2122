#include "tasks/MakingProductTask.h"
#include "Arduino.h"
#include "devices/servo_motor_impl.h"
#include "config.h"
// #include "Logger.h"

#define TOT_MAKING_STEPS 30

MakingProductTask::MakingProductTask(CoffeeMachine* pCM): 
    pCoffeeMachine(pCM) {
    pMotor = new ServoMotorImpl(SERVO_PIN);
    setState(IDLE);
}
  
void MakingProductTask::tick(){
    switch (state){    
    case IDLE: {
        if (pCoffeeMachine->isMakingProduct()){
            currentMakingStep = 0;
            pMotor->on();
            setState(MAKING);
        }
        break;
    }
    case MAKING: {
        currentMakingStep++;
        long angle = map (currentMakingStep, 0, TOT_MAKING_STEPS, 0, 180);
        pMotor->setPosition(angle);
        if (currentMakingStep > TOT_MAKING_STEPS){
            pCoffeeMachine->notifyProductReady();
            setState(WAITING_FOR_REMOVAL);
        } 
        break;       
    }

    case WAITING_FOR_REMOVAL: {
        if (pCoffeeMachine->isProductRemoved()){
            pMotor->setPosition(0);
            setState(REMOVED);
        }
        break;
    }

    case REMOVED: {
        if (elapsedTimeInState() > 1000){
            pMotor->off();
            setState(IDLE);
        }
        break;
    }}
}

void MakingProductTask::test(){
  pMotor->on();
  for (int i = 0; i < 30; i++) {
    pMotor->setPosition(i*6);         
    delay(15);            
  }
  pMotor->setPosition(0);
  pMotor->off();
}
void MakingProductTask::setState(int s){
    state = s;
    stateTimestamp = millis();
}

long MakingProductTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}

ServoMotor* MakingProductTask::getMotor(){
    return pMotor;
}