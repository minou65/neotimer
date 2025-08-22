#include <neotimer.h>

Neotimer mytimer = Neotimer(2000); // 2 second interval
const int LED = 13;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
}

void loop() {
  if (mytimer.repeat()) {
    Serial.println("This prints every 2 seconds (unlimited)");
    digitalWrite(LED, !digitalRead(LED));
  }
}
