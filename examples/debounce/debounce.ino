#include <neotimer.h>

Neotimer timer = Neotimer(1000);
const int Button_Pin = 8;
const int LED_Pin = 13;

void setup() {
  Serial.begin(9600);
  pinMode(Button_Pin,INPUT);
  pinMode(LED_Pin, OUTPUT);

  timer.start();
}

void loop() {
  timer.debounce(digitalRead(Button_Pin));
  if(timer.getDebouncedState()){
    Serial.println("Button pressed");  
  }
}
