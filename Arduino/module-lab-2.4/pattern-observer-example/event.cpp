#include "event.h"
#include "Arduino.h"
#include "EnableInterrupt.h"

/* The singleton interrupt dispatcher, binding interrupts to event sources */
InterruptDispatcher interruptDispatcher;

/* 
 * Functions called by the interrupt handlers, used to notify interrupts to
 * to the interrupt dispatcher
 */
void notifyInterrupt_0(){ interruptDispatcher.notifyInterrupt(0); }
void notifyInterrupt_1(){ interruptDispatcher.notifyInterrupt(1); }
void notifyInterrupt_2(){ interruptDispatcher.notifyInterrupt(2); }
void notifyInterrupt_3(){ interruptDispatcher.notifyInterrupt(3); }
void notifyInterrupt_4(){ interruptDispatcher.notifyInterrupt(4); }
void notifyInterrupt_5(){ interruptDispatcher.notifyInterrupt(5); }
void notifyInterrupt_6(){ interruptDispatcher.notifyInterrupt(6); }
void notifyInterrupt_7(){ interruptDispatcher.notifyInterrupt(7); }
void notifyInterrupt_8(){ interruptDispatcher.notifyInterrupt(8); }
void notifyInterrupt_9(){ interruptDispatcher.notifyInterrupt(9); }
void notifyInterrupt_10(){ interruptDispatcher.notifyInterrupt(10); }
void notifyInterrupt_11(){ interruptDispatcher.notifyInterrupt(11); }
void notifyInterrupt_12(){ interruptDispatcher.notifyInterrupt(12); }
void notifyInterrupt_13(){ interruptDispatcher.notifyInterrupt(13); }


InterruptDispatcher::InterruptDispatcher(){
  notifyFunctions[0] = notifyInterrupt_0;
  notifyFunctions[1] = notifyInterrupt_1;
  notifyFunctions[2] = notifyInterrupt_2;
  notifyFunctions[3] = notifyInterrupt_3;
  notifyFunctions[4] = notifyInterrupt_4;
  notifyFunctions[5] = notifyInterrupt_5;
  notifyFunctions[6] = notifyInterrupt_6;
  notifyFunctions[7] = notifyInterrupt_7;
  notifyFunctions[8] = notifyInterrupt_8;
  notifyFunctions[9] = notifyInterrupt_9;
  notifyFunctions[10] = notifyInterrupt_10;
  notifyFunctions[11] = notifyInterrupt_11;
  notifyFunctions[12] = notifyInterrupt_12;
  notifyFunctions[13] = notifyInterrupt_13;
}
    
void InterruptDispatcher::bind(int pin, EventSource* src){
  sourceRegisteredOnPin[pin] = src;
  enableInterrupt(pin, notifyFunctions[pin], CHANGE);  
}

void InterruptDispatcher::notifyInterrupt(int pin){
  Serial.print("");  /* bug/race fix */
  sourceRegisteredOnPin[pin]->notifyInterrupt(pin);
}

/* ------------------- EventSource ----------------- */

void EventSource::bindInterrupt(int pin){
  interruptDispatcher.bind(pin, this);
}
