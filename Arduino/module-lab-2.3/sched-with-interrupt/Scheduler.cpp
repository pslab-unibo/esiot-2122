#include "Scheduler.h"
#include "Arduino.h"
#include <avr/sleep.h>
#include <avr/power.h>

void Scheduler::init(int basePeriod){
  this->basePeriod = basePeriod;
  timer = new Timer();
  timer->setupPeriod(basePeriod);  
  nTasks = 0;
  Serial.begin(9600);
}

bool Scheduler::addTask(Task* task){
  if (nTasks < MAX_TASKS-1){
    taskList[nTasks] = task;
    nTasks++;
    return true;
  } else {
    return false; 
  }
}

/*
 * Enter sleep mode, with Timer 1 active
 */

void Scheduler::sleep(){
  delay(50); /* fix needed to make it work */

  set_sleep_mode(SLEEP_MODE_IDLE);
  sleep_enable();

  /* Disable all of the unused peripherals. This will reduce power
   * consumption further and, more importantly, some of these
   * peripherals may generate interrupts that will wake our Arduino from
   * sleep!
   */
  power_adc_disable();
  power_spi_disable();
  power_timer0_disable();
  power_timer2_disable();
  power_twi_disable();  
  /* Now enter sleep mode. */
  sleep_mode();  
  /* The program will continue from here after the timer timeout*/
  sleep_disable(); /* First thing to do is disable sleep. */
  /* Re-enable the peripherals. */
  power_all_enable();  
}

void Scheduler::schedule(){
  // Serial.println("BEFORE");
  sleep();
  // Serial.println("READY");
  /** The program will continue from here. **/ 
  for (int i = 0; i < nTasks; i++){
    if (taskList[i]->updateAndCheckTime(basePeriod)){
      taskList[i]->tick();
    }    
  } 
}
