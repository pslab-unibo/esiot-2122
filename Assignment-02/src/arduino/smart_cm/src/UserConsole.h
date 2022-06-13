#ifndef __USER_CONSOLE__
#define __USER_CONSOLE__

#include "config.h"
#include "devices/Pot.h"
#include "devices/Pir.h"
#include "devices/Button.h"
#include "devices/light.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "model/CoffeeMachine.h"

class UserConsole {

public:
  UserConsole();

  void init();
  void sync();

  void showWelcome();
  void showReady();
  void clearMsg();
  
  bool isUpPressed();
  bool isDownPressed();
  bool isMakePressed();

  int getSugarLevel();

  void showItem(ProductType* pItem);
  void showMaking(ProductType* pItem);
  void showProductReady(ProductType* pItem);
  void showUpdatedSugarLevel(int level);
  void showSelfTest();
  void showNeedAssistanceNoMoreItems();
  void showNeedAssistanceFailedSelfTest();
  void testButtons();

  // void calibrate();
  bool detectedPresence();
  void sleep();

  void notifyNumItems(int nItems);
  void notifyNumSelfTests(int nSelfTests);

  bool checkCmd(bool& refilled, bool& recovered);

private:
  Potentiometer* pPot;
  Pir* pPir;
  Button* pButUp; 
  Button* pButDown; 
  Button* pButMake; 
  LiquidCrystal_I2C* pLcd; 
};

#endif
