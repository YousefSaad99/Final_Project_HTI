// Include the necessary files
#include "moveXZ.h"
#include "pickup.h"
#include "Conveyor.h"

void setup() {
  // Initialize ultrasonic sensor and stepper motor pins
  setupUltrasonic();
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(Z_STEP_PIN, OUTPUT);
  pinMode(Z_DIR_PIN, OUTPUT);
  pinMode(PICKUP_STEP_PIN, OUTPUT);
  pinMode(PICKUP_DIR_PIN, OUTPUT);

  setup_conveyor()
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
  conveyor()  // step 1

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
  conveyor()  // step 1

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
  conveyor()  // step 1

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