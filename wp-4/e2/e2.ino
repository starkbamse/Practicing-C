// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 4
// Exercise 2
// Submission code: xxxxxxx

// LINK: https://www.tinkercad.com/things/f3YRB3KPzpE

// Include section
// We use the Servo library to move the the Micro servo
#include <Servo.h>

// Define section
// It was meant to use Timer1 for this exercise. However, upon experimentation, it was fond that the servo library
// uses Timer1. Therefore, we resorted to use Timer0 with  pre-scaler of 1024 giving us a 15.625 KHz clock ticking.
// according to the formula mentioned in the last exercise -> 15625 / (COMPARE_MATCH_VAL + 1) = 1
// Solving for COMPARE_MATCH_VAL we get 15624. However, Timer0 is 8-bit and the max COMPARE_MATCH_VAL it can take is 255.
// So instead we decided to use 24 as the COMPARE_MATCH_VAL. The reason is: 15624 / 24 = 651
// This means that every 561 times that the ISR has happened is as if one second has passed. This work-around was used for this
// exercise.
#define COMPARE_MATCH_VAL 24
#define ISR_TRIGGER_PER_SEC 651
#define MAX_ANG 180
#define MIN_ANG 0
#define SERVO_PIN 11
#define ANGLE_TO_TURN_PER_SEC 3
#define TIMER_VAL 60

// --- Function declaration ---
// Moves the Micro Servo in both directions
void moveServo();
// --- Function declaration ---

// --- Variable declaration ---
// Servo object, to be used to move the servo and set pinMode
Servo servo;
// Servo's angle, to be used to know if the servo should move forward or backwards
volatile uint8_t angle = 0;
// Boolean variable used to see if the servo should move forward or backwards
volatile uint8_t forwardMove = 1;
// Keep seconds counted since the program started
volatile unsigned int secondCounter = TIMER_VAL;
// Keep the number of times the interrupt has taken place
volatile uint16_t interruptCounter = 0;
// --- Variable declaration ---

/**
 * This  program counts seconds using Timer interruptions. Every second that is passed, the second counter
 * variable is incremented, the seconds are printed, and the servo motor moves ANGLE_TO_TURN_PER_SEC degrees.
*/

// Setup function, where pinModes are set and Timer0 register values are set
void setup() {
    // this function sets pinMode(11, INPUT);
	servo.attach(11);
    // Disable interrupts while setting Timer0
    noInterrupts();
    // Initialise Timer0 with registers set to 0
    TCCR0A = 0;
    TCCR0B = 0;
    // Set the clock counter to 0
    TCNT0 = 0;
    // This registers holds the required number of ticks needed to trigger the interrupt
    OCR0A = COMPARE_MATCH_VAL;
    // Turn on CTC mode by setting bit number 1 to 1
    TCCR0A |= ( 1 << WGM01);
    // Set pre-scaler to 1024 by setting bit number 0 and 2 to 1
    TCCR0B |= (1 << CS00) | (1 << CS02);
    // Set bit number of one of the Timer mask to 1 to enable interrupts when TCNT0 value reaches OCR0A
    TIMSK0 |= (1 << OCIE0A);

    // Enable interrupts again
    interrupts();

    // Begin the serial monitor and enable it to transfer 9600 bits per second
    Serial.begin(9600);
}

// Loop function, where statements are run forever
void loop() {

}

void moveServo() {
    // If angle is 0, then set forwardMove to 1 (true) as the servo must move forward
    if (angle == 0) {
        forwardMove = 1;
    }

    // If angle is 180, then set forwardMove to 0 (false) as the servo must move backwards
    if (angle == 180) {
        forwardMove = 0;
    }

    // If forwardMove is true, increase the angle by the amount ANGLE_TO_TURN_PER_SEC
    // Then use the write function (passing angle as an argument) of the servo to move the servo
    if (forwardMove == 1) {
        angle = angle + ANGLE_TO_TURN_PER_SEC;
        servo.write(angle);
    // Else, forwardMove is false, decrease the angle by the amount ANGLE_TO_TURN_PER_SEC
    // Then, move servo backwards
    } else {
        angle = angle - ANGLE_TO_TURN_PER_SEC;
        servo.write(angle);
    }
}

// This is the interrupt service which is triggered NUM_OF_INCREMENTS_TO_SEC times per second.
ISR(TIMER0_COMPA_vect) {
    // Increment the number of times the ISR is triggered by 1, each time it is triggered
    interruptCounter++;
    // If the ISR has happened ISR_TRIGGER_PER_SEC times, then it has been one sec.
    // Increment the second counter by 1, print the seconds and then move the servo
    // to show that a second has passed.
    if (interruptCounter == ISR_TRIGGER_PER_SEC) {
        // If The counter has reached 0, set it back to TIMER_VAL and start again
        if (secondCounter == 0) {
            secondCounter = TIMER_VAL;
        }
        secondCounter--;

        Serial.print("Seconds: ");
        Serial.println(secondCounter);
        moveServo();
        // Set the interrupt counter to 0 for the next second to be counted.
        interruptCounter = 0;
    }

}