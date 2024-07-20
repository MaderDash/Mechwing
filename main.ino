#include <Wire.h>

// Constants
const int I2C_ADDR 								= 0x34; // I2C address of the motor controller
const int MOTOR_FIXED_SPEED_ADDR 	= 51;  // Motor fixed speed address

/*
 * Motor instructions:
 * Each instruction is an array of 4 integers, representing the speed and direction
 * of the left and right motors.
 */
const int FORWARD[] 		= { 23,  23, 0, 0};
const int RETREAT[] 		= {-23, -23, 0, 0};
const int TURN_LEFT[] 	= { 20, -20, 0, 0};
const int TURN_RIGHT[] 	= {-20,  20, 0, 0};
const int STOP[] 				= {  0,   0, 0, 0};

void setup() {
  /*
   * Initialize the I2C bus and serial communication for debugging
   */
  Wire.begin();  				// Initialize I2C bus
  Serial.begin(9600);  	// Initialize serial communication for debugging
}

/*
 * Write motor data to the motor controller
 * @param data: an array of 4 integers representing the motor speeds and directions
 */
void writeMotorData(const int data[]) {
  for (int i = 0; i < 4; i++) {
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(MOTOR_FIXED_SPEED_ADDR + i);
    Wire.write(data[i] & 0xFF);
    Wire.endTransmission();
  }
}

/*
 * Move the robot forward
 */
void moveForward() {
  writeMotorData(FORWARD);
}

/*
 * Move the robot backward
 */
void moveRetreat() {
  writeMotorData(RETREAT);
}

/*
 * Turn the robot left
 */
void turnLeft() {
  writeMotorData(TURN_LEFT);
}

/*
 * Turn the robot right
 */
void turnRight() {
  writeMotorData(TURN_RIGHT);
}

/*
 * Stop the robot
 */
void stop() {
  writeMotorData(STOP);
}

void loop() {
  /*
   * Example usage: move forward for 2 seconds, then stop
   */
  moveForward();
  delay(2000);
  stop();
  delay(2000);
}