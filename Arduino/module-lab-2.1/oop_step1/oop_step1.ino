#include "counter.h"

Counter c(10);
Counter* c1;

void setup(){
  Serial.begin(9600); 
  c1 = new Counter(20);
}

void loop(){
  int x = 0;
  
  Counter* c2 = new Counter(20);
  Serial.println(String("stack at: ") + ((int)(&x)) + " heap at: " + ((int)c2));
  delay(100);
  /*  
  c.inc();
  Serial.println(c.getValue());
  c1->inc();
  Serial.println(c1->getValue());
  delay(1000);
  */
}
