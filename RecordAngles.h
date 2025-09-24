#ifndef RECORDANGLES_H
#define RECORDANGLES_H

#include <Arduino.h>
#include <Servo.h>

// ------------------- Configuration -------------------
#define SERVO_COUNT 6
#define MAX_STEPS 10

// Servo pins
const int servoPins[SERVO_COUNT] = {3, 5, 6, 9, 10, 11};

// Potentiometer pins
const int potPins[SERVO_COUNT] = {A0, A1, A2, A3, A4, A5};

// Push button for recording
#define RECORD_BUTTON 2

// ------------------- Variables -------------------
int recordedAngles[MAX_STEPS][SERVO_COUNT];
int stepCount = 0;

Servo servos[SERVO_COUNT];

// ------------------- Setup -------------------
void setupRecordAngles() {
  for (int i = 0; i < SERVO_COUNT; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(90);
  }
  pinMode(RECORD_BUTTON, INPUT_PULLUP);

  Serial.begin(9600);
}

// ------------------- Record -------------------
void recordAngles() {
  // Live control with pots
  for (int i = 0; i < SERVO_COUNT; i++) {
    int angle = map(analogRead(potPins[i]), 0, 1023, 0, 180);
    servos[i].write(angle);
  }

  // Save when Record button pressed
  if (digitalRead(RECORD_BUTTON) == LOW && stepCount < MAX_STEPS) {
    delay(300); // debounce

    for (int i = 0; i < SERVO_COUNT; i++) {
      recordedAngles[stepCount][i] = map(analogRead(potPins[i]), 0, 1023, 0, 180);
    }

    Serial.print("Recorded Step "); Serial.println(stepCount + 1);
    stepCount++;
  }
}

// ------------------- Play -------------------
void playRecordedAngles() {
  for (int s = 0; s < stepCount; s++) {
    for (int i = 0; i < SERVO_COUNT; i++) {
      servos[i].write(recordedAngles[s][i]);
    }
    delay(1000);
  }
}

#endif
