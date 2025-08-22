#include <neotimer.h>

Neotimer mytimer = Neotimer(5000); // 5 second timer
const int BTN_SHOW = 4;

void setup() {
  Serial.begin(9600);
  pinMode(BTN_SHOW, INPUT);
  mytimer.start();
}

void loop() {
  if (digitalRead(BTN_SHOW) == HIGH) {
    unsigned long elapsed = mytimer.getEllapsed();
    Serial.print("Elapsed time: ");
    Serial.print(elapsed);
    Serial.println(" ms");
    delay(300); // debounce
  }
  if (mytimer.done()) {
    Serial.println("Timer finished!");
    mytimer.reset();
    mytimer.start();
  }
}
