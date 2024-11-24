#define X_STEP_PIN 9
#define X_DIR_PIN  6
#define Z_STEP_PIN 10
#define Z_DIR_PIN  8

#define PICKUP_STEP_PIN 11
#define PICKUP_DIR_PIN 7

// Define trigger and echo pins for Ultrasonic Sensor 1
const int triggerPin1 = 4;
const int echoPin1 = 3;

// Define trigger and echo pins for Ultrasonic Sensor 2
const int triggerPin2 = 1;
const int echoPin2 = 0;

// Define the dc motor pins for conveyor
const int motorPin1 = 13;
const int motorPin2 = 2;

// Define the motor pin
// const int motorE1 = 6;

// Threshold distance (in cm) to detect an object
const float objectThreshold = 20.0; //%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



static bool conveyor_done = false;

// Steps per movement unit for the pickup motor
const int steps_per_unit_pickup = 200; // distance to be moved

static bool pickup_done = false;  // default

// Steps per unit (mm)
const int steps_per_unit_X = 100;
const int steps_per_unit_Z = 100;

// Speed controller delay
const int step_delay = 50;  // Delay between every step (speed of the stepper) %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// Static variables to remember the last position
static int x_position = 0;
static int z_position = 0;

// Flag
static bool item_loaded = false;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void moveTo(int x_target, int z_target) {


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
      delayMicroseconds(step_delay); // 50ms
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

  if(x_position == 0 && z_position == 0){
    pickup_done = false;
    item_loaded = false;
  }

}
////////////////////////////////////////////////////////////////////////////////


void pickUp() {  // direction to pick the item ( forward )

  if(!pickup_done){
    // Move forward (set direction forward)
    digitalWrite(PICKUP_DIR_PIN, HIGH);
    for (int i = 0; i < steps_per_unit_pickup; i++) {
      digitalWrite(PICKUP_STEP_PIN, HIGH);
      delayMicroseconds(100);  // Control speed
      digitalWrite(PICKUP_STEP_PIN, LOW);
      delayMicroseconds(100);
    }

    moveTo(x_position,z_position + 1); // to pick the item 

    delay(1000);

    digitalWrite(PICKUP_DIR_PIN, LOW);   // direction back whith the item  ( backward )
    for (int i = 0; i < steps_per_unit_pickup; i++) {
      digitalWrite(PICKUP_STEP_PIN, HIGH);
      delayMicroseconds(100);  // Control speed
      digitalWrite(PICKUP_STEP_PIN, LOW);
      delayMicroseconds(100);
    }

    moveTo(x_position,z_position - 1); // to pick the item
  }
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  else{
      // Move forward (set direction forward)
    digitalWrite(PICKUP_DIR_PIN, HIGH);
    for (int i = 0; i < steps_per_unit_pickup; i++) {
      digitalWrite(PICKUP_STEP_PIN, HIGH);
      delayMicroseconds(100);  // Control speed
      digitalWrite(PICKUP_STEP_PIN, LOW);
      delayMicroseconds(100);
    }

    moveTo(x_position,z_position - 1); // to pick the item 

    delay(1000);

    digitalWrite(PICKUP_DIR_PIN, LOW);   // direction back whith the item  ( backward )
    for (int i = 0; i < steps_per_unit_pickup; i++) {
      digitalWrite(PICKUP_STEP_PIN, HIGH);
      delayMicroseconds(100);  // Control speed
      digitalWrite(PICKUP_STEP_PIN, LOW);
      delayMicroseconds(100);
    }

    moveTo(x_position,z_position + 1); // to pick the item
  }

  // Set flag pickup is done
  pickup_done = true;

  conveyor_done = false;

}

////////////////////////////////////////////////////////////////////////////////////



void setup_conveyor() {
    // Set the ultrasonic sensor pins as OUTPUT (trigger) and INPUT (echo)
    pinMode(triggerPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(triggerPin2, OUTPUT);
    pinMode(echoPin2, INPUT);

    // Set the motor pin as OUTPUT
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);

    // Start with the motor turned off
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
}

void conveyor() {
    // Measure distance from both ultrasonic sensors
    float distance1 = measureDistanceCm(triggerPin1, echoPin1);
    float distance2 = measureDistanceCm(triggerPin2, echoPin2);
    
    // Check if the object is detected by Sensor 1
    if (distance1 > 0 && distance1 < objectThreshold) {
        // Start the motor if an object is detected by Sensor 1
        delay(10000);
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, HIGH);    
        }

    // Check if the object is detected by Sensor 2
    if (distance2 > 0 && distance2 < objectThreshold) {
        // Stop the motor if an object is detected by Sensor 2
        digitalWrite(motorPin1, LOW);
        digitalWrite(motorPin2, LOW);    
        }

    conveyor_done = true;

    
}

// Function to measure distance in cm using the ultrasonic sensor
float measureDistanceCm(int triggerPin, int echoPin) {
    // Send a 10µs pulse to trigger the sensor
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    // Measure the time it takes for the echo to return (in microseconds)
    long duration = pulseIn(echoPin, HIGH);

    // Calculate the distance in centimeters (speed of sound is 0.0343 cm/us)
    float distance = (duration / 2.0) * 0.0343;

    // Return -1 if the distance exceeds 400 cm (out of range)
    if (distance > 400) {
        return -1.0;
    }

    return distance;
}



///###################################################################################################################################################
void setup() {
  // Initialize ultrasonic sensor and stepper motor pins
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(PICKUP_STEP_PIN, OUTPUT);
  pinMode(PICKUP_DIR_PIN, OUTPUT);

  setup_conveyor();
}

void loop() {
  system_box1();
  system_box2();
  system_box3();
}

// Flags that will control the system workflow
/* 
conveyor_done
pickup_done
item_loaded
*/

void system_box1(){
 
  // check item in the conveyor pickup position
  conveyor();  // step 1

  if (conveyor_done){  // flag from conveyor.h
    pickUp(); // step 2
  }

  delay(1000);

  if (pickup_done){   // flag from pickup.h
      moveTo(5,5); // step 3
  }

  delay(1000);

  if (item_loaded){   // flag from moveXZ.h
    pickUp(); // step 4  >> load item to the shelf
  }

  delay(1000);

  if (pickup_done){
    moveTo(0,0); // step 5 last step, the arm will go back to the start postion 0,0
  }

  delay(1000);
}

void system_box2(){
 
  // check item in the conveyor pickup position
  conveyor();  // step 1

  if (conveyor_done){  // flag from conveyor.h
    pickUp(); // step 2
  }

  delay(1000);

  if (pickup_done){   // flag from pickup.h
      moveTo(5,4); // step 3         /////////////////////////// adjustable
  }

  delay(1000);

  if (item_loaded){   // flag from moveXZ.h
    pickUp(); // step 4  >> load item to the shelf
  }

  delay(1000);

  if (pickup_done){
    moveTo(0,0); // step 5 last step, the arm will go back to the start postion 0,0
  }

  delay(1000);
}

void system_box3(){
 
  // check item in the conveyor pickup position
  conveyor();  // step 1

  if (conveyor_done){  // flag from conveyor.h
    pickUp(); // step 2
  }

  delay(1000);

  if (pickup_done){   // flag from pickup.h
      moveTo(5,3); // step 3   /////////////////////////// adjustable
  }

  delay(1000);

  if (item_loaded){   // flag from moveXZ.h
    pickUp(); // step 4  >> load item to the shelf
  }

  delay(1000);

  if (pickup_done){
    moveTo(0,0); // step 5 last step, the arm will go back to the start postion 0,0
  }

  delay(1000);

  while(true);
}


/////////////////////////////////////////////////////////////////////
