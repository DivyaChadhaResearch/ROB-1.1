#include "RecordAngles.h"

#define PLAY_BUTTON 4

void setup() {
  pinMode(PLAY_BUTTON, INPUT_PULLUP);
  setupRecordAngles();
}

void loop() {
  // Always check for record button (independent trigger)
  recordAngles();

  // If play button pressed → replay
  if (digitalRead(PLAY_BUTTON) == LOW) {
    delay(300);
    playRecordedAngles();
  }
}
