#ifndef __USERMANTASK__
#define __USERMANTASK__

#include "kernel/Task.h"
#include "UserConsole.h"
#include "model/CoffeeMachine.h"

class UserInteractionManTask: public Task {

public:
  UserInteractionManTask(UserConsole* pConsole, CoffeeMachine* pCM); 
  void tick();

private:  
  void setState(int state);
  bool justEnteredInState();
  long elapsedTimeInState();

  bool itemSelected;
  long itemSelectionTime;

  enum { BOOTING, WELCOME, READY, MAKING, PRODUCT_READY, DOING_SELF_TEST, NEED_ASSISTANCE, SLEEPING } state;
  bool isJustEnteredInState;

  long stateTimestamp;
  long lastTimeDetectedPres;

  UserConsole* pConsole;
  CoffeeMachine* pCoffeeMachine;
};

#endif