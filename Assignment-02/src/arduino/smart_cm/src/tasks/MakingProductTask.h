#ifndef __MAKING_PROD_TASK__
#define __MAKING_PROD_TASK__

#include "kernel/Task.h"
#include "model/CoffeeMachine.h"
#include "devices/servo_motor.h"

class MakingProductTask: public Task {

public:
  MakingProductTask(CoffeeMachine* pCM); 
  void tick();

  ServoMotor* getMotor();
  void test();

private:  
  int currentMakingStep;
  
  void setState(int state);
  long elapsedTimeInState();

  enum { IDLE, MAKING, WAITING_FOR_REMOVAL, REMOVED} state;
  long stateTimestamp;

  CoffeeMachine* pCoffeeMachine;
  ServoMotor* pMotor;
};

#endif