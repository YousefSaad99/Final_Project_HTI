#include "moveXZ.h"
#include "pickup.h"
#include "Conveyor.h"

// Define trigger and echo pins for Ultrasonic Sensor 1
const int triggerPin1 = 4;
const int echoPin1 = 3;

// Define trigger and echo pins for Ultrasonic Sensor 2
const int triggerPin2 = 1;
const int echoPin2 = 0;

// Define the motor pin
const int motorPin1 = 13;
const int motorPin2 = 2;

// Define the motor pin
// const int motorE1 = 6;

// Threshold distance (in cm) to detect an object
const float objectThreshold = 20.0;



static bool conveyor_done = false;



void setup_conveyor() {
    // Set the ultrasonic sensor pins as OUTPUT (trigger) and INPUT (echo)
    pinMode(triggerPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(triggerPin2, OUTPUT);
    pinMode(echoPin2, INPUT);

    // Set the motor pin as OUTPUT
    pinMode(motorPin, OUTPUT);

    // Start with the motor turned off
    digitalWrite(motorPin, LOW);
}

void conveyor() {
    // Measure distance from both ultrasonic sensors
    float distance1 = measureDistanceCm(triggerPin1, echoPin1);
    float distance2 = measureDistanceCm(triggerPin2, echoPin2);
    
    // Check if the object is detected by Sensor 1
    if (distance1 > 0 && distance1 < objectThreshold) {
        // Start the motor if an object is detected by Sensor 1
        delay(10000);
        digitalWrite(motorPin, HIGH);
    }

    // Check if the object is detected by Sensor 2
    if (distance2 > 0 && distance2 < objectThreshold) {
        // Stop the motor if an object is detected by Sensor 2
        digitalWrite(motorPin, LOW);
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
