#include "UserConsole.h"
#include "Arduino.h"
// #include "Logger.h"
#include "devices/ButtonImpl.h"
#include "devices/Led.h"
#include "kernel/MsgService.h"
#include <avr/sleep.h>
#include "model/CoffeeMachine.h"
#include "config.h"

void wakeUp(){}

UserConsole::UserConsole(){
  pLcd = new  LiquidCrystal_I2C(0x27,20,4);
  pPot = new Potentiometer(POT_PIN);
  pPir = new Pir(PIR_PIN);
  pButUp = new ButtonImpl(BT_UP_PIN);
  pButDown = new ButtonImpl(BT_DOWN_PIN);
  pButMake = new ButtonImpl(BT_MAKE_PIN);
  attachInterrupt(digitalPinToInterrupt(PIR_PIN), wakeUp, RISING); 
}

void UserConsole::init(){
  pLcd->init();
  pLcd->backlight();
}

int UserConsole::getSugarLevel(){
  return pPot->getValue()*100;
}

void UserConsole::sync(){
  pButDown->sync();
  pButUp->sync();
  pButMake->sync();
  pPot->sync();
  pPir->sync();
}

void UserConsole::showWelcome(){
  pLcd->clear();
  pLcd->setCursor(1,1);
  pLcd->print("WELCOME");  
  MsgService.sendMsg("cm:we");
}

void UserConsole::showReady(){
  pLcd->clear();
  pLcd->setCursor(1,1);
  pLcd->print("Ready.");
  MsgService.sendMsg("cm:ok");
}

void UserConsole::showUpdatedSugarLevel(int value){
  pLcd->setCursor(1,3);
  pLcd->print(String("Sugar level: ") + value + "  ");
}

void UserConsole::clearMsg(){
  pLcd->clear();
}

void UserConsole::showItem(ProductType* pItem){
  pLcd->clear();
  pLcd->setCursor(1,1);
  pLcd->print(pItem->getName());
  pLcd->setCursor(1,2);
  pLcd->print(String("Avail Items: ") + pItem->getNumProducts() + "  ");
  
}

bool UserConsole::isUpPressed(){
  return pButUp->isClicked();
}

bool UserConsole::isDownPressed(){
  return pButDown->isClicked();
}

bool UserConsole::isMakePressed(){
  return pButMake->isClicked();
}

void UserConsole::showMaking(ProductType* pItem){
  pLcd->clear();
  pLcd->setCursor(1,1);
  pLcd->print(String("Making a ") + pItem->getName());
  MsgService.sendMsg("cm:ma");
}

void UserConsole::showProductReady(ProductType* pItem){
  pLcd->setCursor(1,1);
  pLcd->print(String("The ") + pItem->getName());
  pLcd->setCursor(1,2);
  pLcd->print("is ready.");
}

void UserConsole::showSelfTest(){
  pLcd->clear();
  pLcd->setCursor(1,1);
  pLcd->print("Self-Test...");
    MsgService.sendMsg("cm:st");

}

void UserConsole::showNeedAssistanceNoMoreItems(){
  pLcd->clear();
  pLcd->setCursor(1,1);
  pLcd->print("Assistance required.");
  pLcd->setCursor(1,2);
  pLcd->print("(no more items)");
  MsgService.sendMsg("cm:as:ni");
}
void UserConsole::showNeedAssistanceFailedSelfTest(){
  pLcd->clear();
  pLcd->setCursor(1,1);
  pLcd->print("Assistance required.");
  pLcd->setCursor(1,2);
  pLcd->print("(failed self-test)");
  MsgService.sendMsg("cm:as:tf");
}

void UserConsole::sleep(){
    MsgService.sendMsg("cm:zz");
    pLcd->noDisplay();
    delay(100);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
    sleep_enable();
    sleep_mode();  
    pLcd->display();
    MsgService.sendMsg("cm:ok");
}

bool UserConsole::detectedPresence(){
  return pPir->isDetected();
}

void UserConsole::testButtons(){
  if (pButUp->isPressed()){
    pLcd->setCursor(1,1);
    pLcd->print("UP");
  }
  if (pButDown->isPressed()){
    pLcd->setCursor(1,1);
    pLcd->print("DOWN");
  }
  if (pButMake->isPressed()){
    pLcd->setCursor(1,1);
    pLcd->print("MAKE");
  }
}

void UserConsole::notifyNumItems(int nItems){
    MsgService.sendMsg(String("cm:ni:") + nItems);
}

void UserConsole::notifyNumSelfTests(int nSelfTests){
    MsgService.sendMsg(String("cm:nt:") + nSelfTests);
}

bool UserConsole::checkCmd(bool& refilled, bool& recovered){
  if (MsgService.isMsgAvailable()){
    Msg* msg = MsgService.receiveMsg();
    if (msg != NULL){
      if (msg->getContent() == "fi"){
        refilled = true;
        recovered = false;
      } else if (msg->getContent() == "re"){
        refilled = false;
        recovered = true;
      }
      delete msg;
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

