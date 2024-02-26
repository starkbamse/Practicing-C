// Include section
#include <stdlib.h>
#include <string.h>

// Define section
#define MOTOR_A_CW 5        // Motor A control clockwise pin
#define MOTOR_A_ANTI_CW 6   // Motor A control counter-clockwise pin
#define CHANNEL_B 3         // Channel B from the DC motor
#define CHANNEL_A 2         // Channel A from the DC motor
#define SPEED_CONTROL 10    // Pin for controlling the speed
#define MAX_PULSE_WIDTH 255 // Uno uses a max value of 255 for PWM signals
#define MIN_PULSE_WIDTH 0   // Minimum pulse width
#define DC_RPM 38.0         // RPMs of DC motor.

// Main program section

/**
 * This program spins a DC motor with encoder and interacts
 * with the user through the Serial terminal. The accepted
 * format is DDDSSSC which stands for Degrees, Speed and clockwise or not.
 * Example: 0900501 will move the motor 90 degrees, clockwise at 50% speed.
 *
 * Purpose: To spin the motor round and round.
 * DIT632
 *
 **/

// Used to spin the motor clockwise
void spinCW();

// Used to spin the motor counter clockwise
void spinCCW();

// Used to store calibration data for the motor
typedef struct {
  float flanksMaxA;
  float flanksMaxB;
  int flanksRisenA;
  int flanksRisenB;
} MotorCalibration;

// Used to calibrate the motor
void calibrateMotor();

// Number of seconds per revolution
volatile int millisPerRevolution = 0;

// Timestamp for when the next revolution should occur
volatile int nextRevolution = 0;

// Boolean switch for if we should count signals from A & B channels
int doCountFlanks = 0;

// User's selected speed
int userSpeed = 0;

// User's selected degrees
int userDegrees = 0;

// User's selected spinning direction
int userCW = 0;

// Whether or not we have a command that we must execute for the user
int pendingCommand = 0;

// If the motor is reading clockwise or not
volatile int CW = 0;

// Calibration for the current motor.
volatile MotorCalibration config = {0, 0, 0, 0};

void setup() {
  // Set Motor A Clockwise controller to output
  pinMode(MOTOR_A_CW, OUTPUT);

  // Set Motor A Counter-Clockwise controller to output
  pinMode(MOTOR_A_ANTI_CW, OUTPUT);

  // Set channel A to an input with a pull-up resistor
  pinMode(CHANNEL_A, INPUT_PULLUP);

  // Set channel A to an input with a pull-up resistor
  pinMode(CHANNEL_B, INPUT_PULLUP);

  // Create interrupt for Channel A signal, for when it is rising
  attachInterrupt(digitalPinToInterrupt(CHANNEL_A), channelAISR, RISING);

  // Create inerrupt for Channel B signal, for when it is rising
  attachInterrupt(digitalPinToInterrupt(CHANNEL_B), channelBISR, RISING);

  // Begin serial communication at 9600 baud
  Serial.begin(9600);

  // Calculate the number of milliseconds per revolution.
  // we can do this by dividing the number of seconds over the RPM
  // and multiplying by 1000.
  millisPerRevolution = (int)((60.0 / DC_RPM) * 1000.0);

  // Set initial direction to be clockwise
  spinCW();

  // Set speed to 100
  setSpeed(100);

  // Delay for one revolution to get a stable signal and reduce noise.
  delay(millisPerRevolution);

  // Activate boolean flag for counting signal data from motor.
  doCountFlanks = 1;

  // Print to serial monitor
  Serial.println("Calibrating clockwise movement...");

  // Calculate for when the next revolution should occur.
  nextRevolution = millis() + millisPerRevolution;

  // Call calibration function
  calibrateMotor();

  // Spin counter-clockwise
  spinCCW();

  // Print to serial monitor
  Serial.println("Calibrating counter-clockwise movement...");

  // Calculate for when the next revolution should occur.
  nextRevolution = millis() + millisPerRevolution;

  // Call calibration function
  calibrateMotor();

  // Once we are finished calibrating, we can stop the motor.
  setSpeed(0);

  // We no longer want to count signals
  doCountFlanks = 0;

  // Set the signal count to 0
  config.flanksRisenA = 0;

  // Set the signal count to 0
  config.flanksRisenB = 0;
}

void loop() {
  String command; // Used to store the users input
  int degrees;    // Number of degrees

  // If we have user input
  if (Serial.available() > 0) {
    // We want to start counting signals
    doCountFlanks = 1;

    // We read the user command in according to the format
    command = Serial.readStringUntil('\n');

    // The first three characters are degree specs
    userDegrees = atoi(command.substring(0, 3).c_str());

    // The second three characaters are speed specs
    userSpeed = atoi(command.substring(3, 6).c_str());

    // The last character is a bool for CW or CCW movement
    userCW = atoi(command.substring(6).c_str());

    // If user selected CW movement
    if (userCW) {
      // Prepare the motor for CW movement.
      spinCW();
    } else {
      // Prepare the motor for CCW movement.
      spinCCW();
    }

    // Set the speed of the motor
    setSpeed(userSpeed);

    // Print a new line
    Serial.println();

    // Print a string
    Serial.print("Degree set: ");

    // Print the degrees we set it to
    Serial.print(userDegrees);

    // Print a string
    Serial.print(" Speed set: ");

    // Print the speed we set  it to
    Serial.print(userSpeed);

    // Print a string
    Serial.print(" Clockwise set: ");

    // Print if we set clockwise or not
    Serial.println(userCW);

    // Set the boolean flag that we have an unfinished movement.
    pendingCommand = 1;
  }

  // Set the number of degrees to 0
  degrees = 0;

  // If we have clockwise movement
  if (userCW) {
    // If the current signal count is above the max
    if (config.flanksRisenA >= config.flanksMaxA) {
      // It means we have gone one full rotation/revolution.
      // Therefore we reset the signal count.
      config.flanksRisenA = 0;
    }
    // Calculate the degrees by taking the absolute error term
    // and mapping it to 0 through 360 degrees
    degrees = map(abs(config.flanksRisenA), 0.0, config.flanksMaxA, 0.0, 360.0);

    // When the motor spins in different directions over time,
    // especially in half rotations or full rotations, the signals
    // get out of sync unnecessarily and grow into very large numbers.
    // We can minimize this by resetting the count of the corresponding
    // signal count to 0 if we are in a neutral position (0).
    if (degrees == 0) {
      // Set the signal count for channel B by reverse mapping the
      // current degrees to its corresponding signal value interval
      // that we have calculated during calibration phase.
      config.flanksRisenB = map(degrees, 0.0, 360.0, 0.0, config.flanksMaxB);
    }

  } else {

    // If the current signal count for B is bigger than max
    if (config.flanksRisenB >= config.flanksMaxB) {
      // Set the signal count to 0.
      config.flanksRisenB = 0;
    }

    // Calculate the degrees by taking the absolute error term
    // and mapping it to 0 through 360 degrees
    degrees = map(abs(config.flanksRisenB), 0.0, config.flanksMaxB, 0.0, 360.0);

    // When the motor spins in different directions over time,
    // especially in half rotations or full rotations, the signals
    // get out of sync unnecessarily and grow into very large numbers.
    // We can minimize this by resetting the count of the corresponding
    // signal count to 0 if we are in a neutral position (0).
    if (degrees == 0) {
      // Set the signal count for channel B by reverse mapping the
      // current degrees to its corresponding signal value interval
      // that we have calculated during calibration phase.
      config.flanksRisenA = map(degrees, 0.0, 360.0, 0.0, config.flanksMaxA);
    }
  }

  // If the current degrees are equal to the requested degrees
  // and we have a pending command from the user
  if (degrees == userDegrees && pendingCommand) {
    // Stop the motor.
    setSpeed(0);
    // Deactivate the command
    pendingCommand = 0;
    // Print out status message
    Serial.print("Completed. Current position: ");
    // Print current degrees.
    Serial.println(degrees);
  }
}

void calibrateMotor() {
  // Set the current signal A count to 0.
  config.flanksRisenA = 0;
  // Set the current signal B count to 0.
  config.flanksRisenB = 0;
  // Perform non-blocking sleep until the
  // theoretical esimation for a revolution
  // has passed.
  while (millis() < nextRevolution)
    ;
  // Print out status message
  Serial.print("Calibration complete. Flanks risen A: ");
  // Print the current signal count for A
  Serial.print(abs(config.flanksRisenA));
  // Print out status message
  Serial.print(" Flanks risen B: ");
  // Print the signal count for B
  Serial.println(abs(config.flanksRisenB));

  // If we are spinning clockwise
  if (CW) {
    // Set the current max signal count to the absolute value of the current
    // count. The reason for doing absolute value is to have less care about the
    // original direction of the signal. Otherwise it becomes rather complex to
    // calculate the degrees.
    config.flanksMaxA = abs(config.flanksRisenA);

  } else {
    // If we are not spinning clockwise
    // Set the current max signal count to the absolute value of the current
    // count. The reason for doing absolute value is to have less care about the
    // original direction of the signal. Otherwise it becomes rather complex to
    // calculate the degrees.
    config.flanksMaxB = abs(config.flanksRisenB);
  }
}

void setSpeed(int speed) {
  // Send a pulse by mapping a speed percentage into a
  // pulse with a width from 0 to 255.
  analogWrite(SPEED_CONTROL, map(speed, 0, 100, 1, 255));
}

void spinCW() {
  // Set the clockwise boolean flag to true
  CW = 1;
  // Set motor A clockwise signal to high
  digitalWrite(MOTOR_A_CW, HIGH);
  // Set motor A counter-clockwise signal to low
  digitalWrite(MOTOR_A_ANTI_CW, LOW);
}

void spinCCW() {
  // Set the clockwise boolean flag to false
  CW = 0;
  // Set motor A clockwise signal to LOW
  digitalWrite(MOTOR_A_CW, LOW);
  // Set motor A counter-clockwise signal to HIGH
  digitalWrite(MOTOR_A_ANTI_CW, HIGH);
}

/*
 * The reason why we add and subtract depending on CW or CCW
 * is because we want to create a balanced signal increase
 * that we can use to calculate the distance from the origin.
 * This is partiularly useful for when we need to return to 0
 * degrees.
 */

void channelAISR() {
  // If we are not supposed to count signals, we exit
  if (!doCountFlanks)
    return;
  // If the motor is spinning clockwise
  if (userCW) {
    // Add to the signal count (error term/ distance from zero)
    config.flanksRisenA++;
  } else {
    // If we are spinning the other way we can decrease the
    // error term / distance from zero as we are approaching zero.
    config.flanksRisenA--;
  }
}
void channelBISR() {
  // If we are not supposed to count signals, we exit
  if (!doCountFlanks)
    return;
  // If the motor is spinning clockwise
  if (userCW) {
    // Since we are spinning clockwise we can decrement from the
    // error term since we are moving away in the other direction
    config.flanksRisenB--;
  } else {
    // If we are spinning CCW we can increment to the error term
    // since we are moving in the CCW direction
    config.flanksRisenB++;
  }
}
