#define TRIG_PIN 8
#define ECHO_PIN 9
#define DISTANCE_THRESHOLD 5  // Distance threshold in cm

// Flag that will trigger the pickup motor
bool object_detected = false;

void setupUltrasonic() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
}

void checkUltrasonic() {
  // Send a 10us pulse to trigger the ultrasonic
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Read the echo time and calculate distance in cm
  long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration * 0.034 / 2;

  // check if the object is at the pickup postion
  if (distance <= DISTANCE_THRESHOLD) {
    object_detected = true;  
  } else {
    object_detected = false;
  }
}
