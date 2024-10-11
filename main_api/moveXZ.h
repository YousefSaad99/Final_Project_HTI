#define X_STEP_PIN 2
#define X_DIR_PIN  5
#define Z_STEP_PIN 3
#define Z_DIR_PIN  6

// Steps per unit (mm)
const int steps_per_unit_X = 100;
const int steps_per_unit_Z = 100;

// Speed controller delay
const int step_delay = 50;  // Delay between every step

// Flag
bool item_loaded = false;

void moveTo(int x_target, int z_target) {
  // Static variables to remember the last position
  static int x_position = 0;
  static int z_position = 0;

  // Calculate the difference between the target and current position
  int x_steps = abs(x_target - x_position) * steps_per_unit_X;  // X-axis steps
  int z_steps = abs(z_target - z_position) * steps_per_unit_Z;  // Z-axis steps

  // Set direction for X-axis
  if (x_target >= x_position) {
    digitalWrite(X_DIR_PIN, HIGH);  // Move in positive direction
  } else {
    digitalWrite(X_DIR_PIN, LOW);   // Move in negative direction
  }

  // Set direction for Z-axis
  if (z_target >= z_position) {
    digitalWrite(Z_DIR_PIN, HIGH);  // Move in positive direction
  } else {
    digitalWrite(Z_DIR_PIN, LOW);   // Move in negative direction
  }

  // Move the motors step by step
  for (int i = 0; i < max(x_steps, z_steps); i++) {
    if (i < x_steps) {
      digitalWrite(X_STEP_PIN, HIGH);
      delayMicroseconds(step_delay);
      digitalWrite(X_STEP_PIN, LOW);
      delayMicroseconds(step_delay);
    }

    if (i < z_steps) {
      digitalWrite(Z_STEP_PIN, HIGH);
      delayMicroseconds(step_delay);
      digitalWrite(Z_STEP_PIN, LOW);
      delayMicroseconds(step_delay);
    }
  }

  // Update the last position to the new target
  x_position = x_target;
  z_position = z_target;
  item_loaded = true;
}
