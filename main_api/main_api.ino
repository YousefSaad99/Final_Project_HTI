// Include the necessary files
#include "received.h"
#include "moveXZ.h"
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
  system();
}

// Flags that will control the system workflow
/* 
item_loaded
object_detected
pickup_done
*/

void system(){
  // check the item is in the pickup postion
  checkUltrasonic();  // step 1

  if (object_detected){
    movePickupMotor(); // step 2
  }
  if (pickup_done){
      moveTo(5,5); // step 3
      pickup_done = false;
  }
  if (item_loaded){
    movePickupMotor(); // step 4 
  }
  if (pickup_done){
    moveTo(0,0); // step 5 last step, the arm will go back to the start postion 0,0
    object_detected = false;
    item_loaded = false;
    pickup_done = false;
  }

}