/*
  Organic Heartbeat Simulator with Salvaged Servo Motors
  -----------------------------------------------------
  This sketch simulates organic heartbeat rhythms using servo motors, ideal for art installations or biofeedback projects.
  Connect each salvaged servo to a PWM-capable pin on your Arduino.
*/

#include <Servo.h>

// Number of salvaged servos
#define NUM_SERVOS 2

// Assign pins for each servo
const int servoPins[NUM_SERVOS] = {9, 10};
Servo servos[NUM_SERVOS];

// Heartbeat rhythm parameters
unsigned long lastBeatTime = 0;
int beatInterval = 800; // ms, average human resting heart rate
int beatPhase = 0;

// Organic rhythm parameters
float irregularity = 0.15; // 0.0 = steady, 0.3 = very irregular

void setup() {
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].attach(servoPins[i]);
    servos[i].write(90); // Neutral position
  }
}

void loop() {
  unsigned long now = millis();
  if (now - lastBeatTime > beatInterval) {
    heartbeat();
    lastBeatTime = now;
    // Add organic irregularity
    beatInterval = 600 + random(-100, 100) + (int)(random(-100, 100) * irregularity);
  }
}

void heartbeat() {
  // Simulate a two-phase heartbeat (systole/diastole)
  for (int phase = 0; phase < 2; phase++) {
    int angle = (phase == 0) ? 60 : 120; // Contract/relax
    for (int i = 0; i < NUM_SERVOS; i++) {
      servos[i].write(angle + random(-5, 5)); // Add slight jitter for organic feel
    }
    delay((phase == 0) ? 120 : 180); // Shorter contraction, longer relaxation
  }
  // Return to neutral
  for (int i = 0; i < NUM_SERVOS; i++) {
    servos[i].write(90);
  }
}
