#include <neotimer.h>

Neotimer mytimer = Neotimer(1000); // Initial value, will be overridden
const int LED = 13;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  if (mytimer.repeat(5, 1500)) { // Repeat 5 times, 1.5s interval
    Serial.println("Blinking every 1.5 seconds, 5 times");
    digitalWrite(LED, !digitalRead(LED));
  }
}
