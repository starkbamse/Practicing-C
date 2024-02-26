// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 6
// Exercise 1
// Submission code:

// Define section
#define LED_MIN 2              // First LED
#define LED_MAX 5              // Last LED
#define PIEZO 9                // Pin of the piezo speaker
#define ULTRASONIC_TRIG 6      // Ultrasonic pin trigger
#define ULTRASONIC_ECHO 7	   // Ultrasonic pin trigger
#define SOUND_SPEED 0.0343     // Sound speed in cms/microsecond
#define MIN_DISTANCE 25.0      // Minimum distance
#define MAX_DISTANCE 200.0     // Maximum distance
#define MIN_LED_THRESHOLD 30.0 // Minimum distance for all LEDs to lit up.
#define ALARM_INTERVAL 250     // N milliseconds for the alarm interval
// Main program section

/**
 * This program measures the distance from the ultrasonic sensor
 * and gives input to the user as an "intruder alarm" using LEDs
 * and a piezo buzzer to alert the user of a possible intruder.
 *
 * Purpose: To protect people against robbery.
 * DIT632
 *
 * https://www.tinkercad.com/things/dhLp5rPxIpO-wp6e2?sharecode=ypmWsPsocguCNZwuzv2i4Tq_GY2OkAMyEf2gOtHsrDk
 *
 **/

// Used to measure the distance using the ultrasonic sensor
float measureDistance();

// Turns on a set amount of LEDs
void turnOnLEDs(int quantity);

// Plays a sound of set annoyingness
void playSound(int annoyingness);

void setup() {
  int i; // To keep track of where we are in loop

  // Begin serial communication at 9600 baud
  Serial.begin(9600);

  // From the first to last LED
  for (i = LED_MIN; i <= LED_MAX; i++) {
    // Set pinmode to output
    pinMode(i, OUTPUT);
  }

  // Set piezo speaker to output
  pinMode(PIEZO, OUTPUT);
  
  pinMode(ULTRASONIC_TRIG, OUTPUT);
  pinMode(ULTRASONIC_ECHO, INPUT);
}

void loop() {
  // Calculate the current distance
  float distance = measureDistance();
  float i; // To keep track of where we are in loop

  // N previous thresholds that were triggered
  // we use this to check whether or not we should
  // change the current signal
  int prevThresholds = 0;

  // N current thresholds triggered
  int thresholdsTriggered;

  // If the current distance is less than max but greater than min
  if (distance <= MAX_DISTANCE && distance >= MIN_DISTANCE) {
    // Set the current thresholds to 0
    thresholdsTriggered = 0;

    // Loop through from the max distance until the minimum distance
    // with iterations of the max-min / 3 because at this point
    // we only have 3 LEDs left to light up. So we want an equal
    // distance for all of them. We calculate this value dynamically,
    // but since it is zero-indexed we add a 1 to it, to include the last LED
    for (i = MAX_DISTANCE; i >= MIN_DISTANCE;
         i -=
         ((MAX_DISTANCE - MIN_LED_THRESHOLD) / (1 + (LED_MAX - LED_MIN)))) {
      // If the current distance is less than the thresholds
      if (distance <= i) {
        // Increment the thresholds
        thresholdsTriggered++;
      }
    }
    // If the number of thresholds triggered was bigger than 0
    if (thresholdsTriggered > 0) {
      // If it equals the previous amount of thresholds, we
      // do not need to update the signal
      if (prevThresholds == thresholdsTriggered)
        return;
      // Turn on N leds according to the number of thresholds triggered.
      turnOnLEDs(thresholdsTriggered);

      // Make the new value the old value
      prevThresholds = thresholdsTriggered;

      // Play sound according to how many thresholds were triggered
      playSound(thresholdsTriggered);
    } else {

      // If we are just within 200cm, we turn on one led
      turnOnLEDs(1);
      // Play the nicest tone
      playSound(1);
    }

  } else if (distance < MIN_DISTANCE) {
    // If the distance is less than the minimum distance
    // we turn off all LEDs and turn them on an interval.
    // Same goes for the piezo speaker.

    // Turn off all LEDs
    turnOnLEDs(0);
    // Stop playing sound
    playSound(0);

    // Delay for the specified alarm interval
    delay(ALARM_INTERVAL);

    // Turn on all LEDs
    turnOnLEDs((1 + (LED_MAX - LED_MIN)));

    // Play sound for the threshold
    playSound((1 + (LED_MAX - LED_MIN)));

    // Delay for specified alarm interval
    delay(ALARM_INTERVAL);

  } else {
    // If we are outside of the valid range

    // Turn off all LEDs
    turnOnLEDs(0);

    // Dont play sound
    playSound(0);
  }
}

float measureDistance() {
  // Used for retrieving time taken to receive pulse
  float timeTaken = 0;

  // Turn off the ultrasonic
  digitalWrite(ULTRASONIC_TRIG, LOW);

  // Delay for 2 ms
  delay(2);

  // Transmit ultrasound
  digitalWrite(ULTRASONIC_TRIG, HIGH);

  // Wait for 10ms
  delay(10);

  // Stop transmitting ultrasound
  digitalWrite(ULTRASONIC_TRIG, LOW);

  // Read the time taken for pulse to come in
  timeTaken = pulseIn(ULTRASONIC_ECHO, HIGH);

  // Return the distance. We divide by
  // two because we only want the distance from
  // the sensor and object, not both ways.
  return (SOUND_SPEED * timeTaken) / 2;
}

void turnOnLEDs(int quantity) {
  int i; // To keep track of where we are in loop

  // The number of leds are zero indexed,
  // hence we must subtract 1 and add it to
  // the minimum LED pin
  quantity = LED_MIN + (quantity - 1);

  // Loop through from the first LED to the last
  for (i = LED_MIN; i <= LED_MAX; i++) {
    // If we have surpassed the allowed max
    // for this loop
    if (i > quantity) {
      // Turn off the LED
      digitalWrite(i, LOW);
    } else {
      // If not, turn on the LED
      digitalWrite(i, HIGH);
    }
  }
}

void playSound(int annoyingness) {
  // If we do not want to play sound
  if (!annoyingness) {
    // Play no tone on the piezo
    noTone(PIEZO);
    return;
  }
  // Play a tone on the piezo, n * 1000 hz signal
  tone(PIEZO, annoyingness * 1000);
}
