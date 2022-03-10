#define LED_PIN 9

int fadeAmount;
int currIntensity;

void setup() {
  currIntensity = 0;
  fadeAmount = 5;
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  analogWrite(LED_PIN, currIntensity); // between 0 and 255
  currIntensity += fadeAmount;
  if (currIntensity >= 255 || currIntensity <= 0){
    fadeAmount = -fadeAmount; 
  }
  delay(20);
}
