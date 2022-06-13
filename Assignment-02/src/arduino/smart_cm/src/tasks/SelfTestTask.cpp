#include "tasks/SelfTestTask.h"
#include "Arduino.h"
#include "config.h"
#include "kernel/Logger.h"
#include "devices/TempSensorLM35.h"

#define TOT_CHECKING_STEPS 8

SelfTestTask::SelfTestTask(CoffeeMachine* pCM, ServoMotor* pM): 
    pCoffeeMachine(pCM), pMotor(pM) {
    pTempSensor = new TempSensorLM35(TEMP_PIN);
    setState(WAITING_TO_CHECK);
}
  
void SelfTestTask::tick(){
    switch (state){    
    case WAITING_TO_CHECK: {
        if (pCoffeeMachine->isIdle() && elapsedTimeInState() > T_SELF_TEST){
            pCoffeeMachine->startSelfTest();
            currentCheckingStep = 0;
            pMotor->on();
            setState(CHECKING_STEP_STAGE_ONE);
        }
        break;
    }
    case CHECKING_STEP_STAGE_ONE: {
        currentCheckingStep++;
        long angle = map (currentCheckingStep, 0, TOT_CHECKING_STEPS, 0, 180);
        pMotor->setPosition(angle);
        if (currentCheckingStep > TOT_CHECKING_STEPS){
            setState(CHECKING_STEP_STAGE_TWO);
        } 
        break;
    }
    case CHECKING_STEP_STAGE_TWO: {
        currentCheckingStep--;
        long angle = map (currentCheckingStep, 0, TOT_CHECKING_STEPS, 0, 180);
        pMotor->setPosition(angle);
        if (currentCheckingStep == 0){
            setState(FINALIZE_CHECK);
        } 
        break;
    }
    case FINALIZE_CHECK: {
        float temp = pTempSensor->getTemperature();
        if (temp < TEMP_MIN || temp > TEMP_MAX){
            pCoffeeMachine->selfTestCompleted(true);
        } else {
            pCoffeeMachine->selfTestCompleted(false);
        } 
        setState(WAITING_TO_CHECK);
        break;
    }}
}


void SelfTestTask::setState(int s){
    state = s;
    stateTimestamp = millis();
}

long SelfTestTask::elapsedTimeInState(){
    return millis() - stateTimestamp;
}
