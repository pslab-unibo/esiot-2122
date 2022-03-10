#define LED_PIN 9
#define BUTTON_PIN 2

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);

}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN);
  if (buttonState == HIGH){
    digitalWrite(LED_PIN, HIGH);  
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  delay(10);
}
