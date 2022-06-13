#ifndef __REMOVE_PROD_TASK__
#define __REMOVE_PROD_TASK__

#include "kernel/Task.h"
#include "model/CoffeeMachine.h"
#include "devices/Sonar.h"

class RemoveProductTask: public Task {

public:
  RemoveProductTask(CoffeeMachine* pCM); 
  void tick();
  void test();

private:  
  
  void setState(int state);
  long elapsedTimeInState();

  enum { IDLE, REMOVING } state;
  long stateTimestamp;

  CoffeeMachine* pCoffeeMachine;
  Sonar* pSonar;
};

#endif