#include "Scheduler.h"
#include "BlinkTask.h"

Scheduler sched;

void setup(){
  
  sched.init(500);
  
  Task* t0 = new BlinkTask(13);
  t0->init(2000);
  sched.addTask(t0);
   
}

void loop(){
  sched.schedule();
}
