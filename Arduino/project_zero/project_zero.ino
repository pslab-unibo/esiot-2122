
#include "lib.h"

int c;

void setup() {
  // put your setup code here, to run once:
  c = 0;
  Serial.begin(115200);
}

void loop() {
  c = inc(c);
  Serial.println(c);
  delay(1000);
  
}
