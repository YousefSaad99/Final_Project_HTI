// Include the necessary files
#include "received.ino"
#include "moveXZ.ino"
#include "pickup.h"

void setup() {
  // Initialize ultrasonic sensor and stepper motor pins
  setupUltrasonic();
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(PICKUP_STEP_PIN, OUTPUT);
  pinMode(PICKUP_DIR_PIN, OUTPUT);
}

void loop() {
  // Check the ultrasonic sensor
  checkUltrasonic();

  // If object is detected, trigger the motor movements
  if (object_detected) {
    // Move from (0, 0) to (10, 0)
    moveTo(10, 0);
    delay(1000);  // Wait 1 second

    // Move from (10, 0) to (10, 10)
    moveTo(10, 10);
    delay(1000);  // Wait 1 second

    // Move back to (0, 0)
    moveTo(0, 0);
    delay(1000);  // Wait 1 second

    // Trigger the pickup motor
    movePickupMotor();

    // Wait for the pickup to complete
    if (pickup_done) {
      // Pickup is done, can add further actions if needed
      // Reset the flags if needed
      object_detected = false;
      pickup_done = false;
    }
  }
}
