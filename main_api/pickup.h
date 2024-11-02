#include "moveXZ.h"
#include "pickup.h"
#include "Conveyor.h"

#define PICKUP_STEP_PIN 11
#define PICKUP_DIR_PIN 7

// Steps per movement unit for the pickup motor
const int steps_per_unit_pickup = 200; // distance to be moved

static bool pickup_done = false;  // default

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
