#include "RecordAngles.h"

#define PLAY_BUTTON 4

void setup() {
  pinMode(PLAY_BUTTON, INPUT_PULLUP);
  setupRecordAngles();
}

void loop() {
    recordAngles();
    if (digitalRead(PLAY_BUTTON) == LOW) {
    delay(300);
    playRecordedAngles();
  }
}
