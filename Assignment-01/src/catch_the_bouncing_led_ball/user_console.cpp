#include "user_console.h"
#include "Arduino.h"
#include "config.h"

#include <EnableInterrupt.h>

#define BOUNCING_TIME 100

uint8_t inputPins[] = {BUT01_PIN, BUT02_PIN, BUT03_PIN, BUT04_PIN};

bool buttonPressedFlags[] = {false, false, false, false};

long lastButtonPressedTimeStamps[NUM_INPUT_POS];

void button_handler(){
  long ts = millis();
  for (int i = 0; i < NUM_INPUT_POS; i++) {
    int status = digitalRead(inputPins[i]);
    if (status == HIGH) {
      if (ts - lastButtonPressedTimeStamps[i] > BOUNCING_TIME){
        buttonPressedFlags[i] = true;      
        lastButtonPressedTimeStamps[i] = ts;
      }
    } else {
        buttonPressedFlags[i] = false;      
        lastButtonPressedTimeStamps[i] = ts;
    }
  }
}

int read_difficulty_level(){
  return map(analogRead(POT_PIN), 0, 1023, 1, DIFFICULTY_LEVELS);
}

void init_player_console(){
  Serial.begin(9600);
  for (int i = 0; i < NUM_INPUT_POS; i++) {
    pinMode(inputPins[i], INPUT);  
    enableInterrupt(inputPins[i], button_handler, CHANGE);       
  }
}

void print_on_console(const String& msg){
  Serial.println(msg);
}

void log(const String& msg){
  Serial.println(msg);
}


void reset_player_input(){
  long ts = millis();
  for (int i = 0; i < NUM_INPUT_POS; i++) {
    buttonPressedFlags[i] = false;      
    lastButtonPressedTimeStamps[i] = ts;    
  }
  delay(BOUNCING_TIME);
}

int get_button_pressed_index() {
 for (int i = 0; i < NUM_INPUT_POS; i++) {
    if (buttonPressedFlags[i]) {
      return i;      
    }
  }
  return NO_SELECTION;
}

bool player_input_started(){
  if (buttonPressedFlags[0]){
    return true;
  } else {
    return false;
  }
}

void test_player_input(){
  for (int i = 0; i < NUM_INPUT_POS; i++) {
    if (buttonPressedFlags[i]) {
      Serial.println(String("button ") + i + " pressed"); 
    }
  }
  int value = analogRead(POT_PIN);
  Serial.println(value);
}
