#ifndef __SELF_TEST_TASK__
#define __SELF_TEST_TASK__

#include "kernel/Task.h"
#include "model/CoffeeMachine.h"
#include "devices/servo_motor.h"
#include "devices/TempSensor.h"

class SelfTestTask: public Task {

public:
  SelfTestTask(CoffeeMachine* pCM, ServoMotor* pMotor); 
  void tick();
  void test();

private:  
  
  void setState(int state);
  long elapsedTimeInState();

  enum { WAITING_TO_CHECK, CHECKING_STEP_STAGE_ONE, CHECKING_STEP_STAGE_TWO, FINALIZE_CHECK } state;
  long stateTimestamp;

  int currentCheckingStep;
  CoffeeMachine* pCoffeeMachine;
  ServoMotor* pMotor;
  TempSensor* pTempSensor;
};

#endif