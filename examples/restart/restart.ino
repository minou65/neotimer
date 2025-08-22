#include <neotimer.h>

Neotimer mytimer = Neotimer(4000); // 4 second timer
const int BTN_STOP = 4;
const int BTN_RESTART = 5;

void setup() {
  Serial.begin(9600);
  pinMode(BTN_STOP, INPUT);
  pinMode(BTN_RESTART, INPUT);
  mytimer.start();
}

void loop() {
  if (digitalRead(BTN_STOP) == HIGH) {
    mytimer.stop();
    Serial.println("Timer stopped");
    delay(300); // debounce
  }
  if (digitalRead(BTN_RESTART) == HIGH) {
    mytimer.restart();
    Serial.println("Timer restarted (continues from where stopped)");
    delay(300); // debounce
  }
  if (mytimer.done()) {
    Serial.println("Timer finished!");
    mytimer.reset();
    mytimer.start();
  }
}
