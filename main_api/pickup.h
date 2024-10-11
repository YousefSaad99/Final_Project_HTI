#define PICKUP_STEP_PIN 10
#define PICKUP_DIR_PIN 11

// Steps per movement unit for the pickup motor
const int steps_per_unit_pickup = 200;
bool pickup_done = false;

void movePickupMotor() {
  // Move forward (set direction forward)
  digitalWrite(PICKUP_DIR_PIN, HIGH);
  for (int i = 0; i < steps_per_unit_pickup; i++) {
    digitalWrite(PICKUP_STEP_PIN, HIGH);
    delayMicroseconds(500);  // Control speed
    digitalWrite(PICKUP_STEP_PIN, LOW);
    delayMicroseconds(500);
  }

  delay(1000);  

  digitalWrite(PICKUP_DIR_PIN, LOW);
  for (int i = 0; i < steps_per_unit_pickup; i++) {
    digitalWrite(PICKUP_STEP_PIN, HIGH);
    delayMicroseconds(500);  // Control speed
    digitalWrite(PICKUP_STEP_PIN, LOW);
    delayMicroseconds(500);
  }

  // Set flag pickup is done
  pickup_done = true;
}
