#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper LRstepper = Stepper(stepsPerRevolution, 8, 10, 9, 11); // y,g,b,p
Stepper UDstepper = Stepper(stepsPerRevolution, 4, 5, 6, 7); // y,g,b,p

void setup() {
    // Nothing to do (Stepper Library sets pins as outputs)
}

void loop() {
	// Rotate CW slowly at 5 RPM
	LRstepper.setSpeed(10);
	LRstepper.step(stepsPerRevolution);
  UDstepper.setSpeed(10);
	UDstepper.step(stepsPerRevolution);
	delay(500);
	
	// Rotate CCW quickly at 10 RPM
	LRstepper.setSpeed(10);
	LRstepper.step(-stepsPerRevolution);
  UDstepper.setSpeed(10);
	UDstepper.step(-stepsPerRevolution);
	delay(500);
}