#include <neotimer.h>

Neotimer mytimer = Neotimer(5000); // 5 second timer
const int BTN_PAUSE = 4;
const int BTN_RESUME = 5;

void setup() {
  Serial.begin(9600);
  pinMode(BTN_PAUSE, INPUT);
  pinMode(BTN_RESUME, INPUT);
  mytimer.start();
}

void loop() {
  if (digitalRead(BTN_PAUSE) == HIGH) {
    mytimer.pause();
    Serial.println("Timer paused");
    delay(300); // debounce
  }
  if (digitalRead(BTN_RESUME) == HIGH) {
    mytimer.resume();
    Serial.println("Timer resumed");
    delay(300); // debounce
  }
  if (mytimer.done()) {
    Serial.println("Timer finished!");
    mytimer.reset();
    mytimer.start();
  }
}
