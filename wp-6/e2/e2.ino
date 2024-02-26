// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 6
// Exercise 2
// Submission code: 


/*
* This program is a parking assistance. It uses an ultrasonic distance sensor to measure the distance
* of an object from the sensor. It turns on LED lights depending on the distance and also plays a 
* buzzer sound when the object is getting closer to the sensor.
**/

#define ULTRASONIC 7 // Define pin for ultrasonic sensor
#define BUZZER 9 // Define pin for the Piezo buzzer
#define MIN_DISTANCE 25 // Minimum distance in cm
#define MAX_DISTANCE 200 // Maximum distance in cm
#define MIN_TONE 10 // Minimum tone frequency for the buzzer
#define MAX_TONE 1000 // Maximum tone frequency for the buzzer

const int ledPins[] = {2, 3, 4, 5}; // Define all 4 LED pins-

int distance; // Distance of the object from the ultrasonic sensor
int duration; // Duration of the echo pulse

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set LED pins as output
  for (int i = 0; i < 4; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  // Set the piexo buzzer as output
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  // Measure distance
  distance = measureDistance();
  Serial.println(distance);
  
  // Display distance using LEDs
  lightLEDs(distance);
  
  // Generate tone based on distance
  generateTone(distance);
  
  delay(100); // Delay a smoother experience
}

int measureDistance() {
  // Set the ultrasonic sensor as an output pin to send the trigger
  pinMode(ULTRASONIC, OUTPUT);
  // Set it to low
  digitalWrite(ULTRASONIC,LOW);
  // Delay for 2 microseconds
  delayMicroseconds(2);
  // Write the ultrasonic sensor to high
  digitalWrite(ULTRASONIC, HIGH);
  // Delay for 5 microseconds
  delayMicroseconds(5);
  // Write it to low again
  digitalWrite(ULTRASONIC,LOW);
  // Now set it to an input pin to receive the echo
  pinMode(ULTRASONIC,INPUT);
  // Get the duration of a pulse
  duration=pulseIn(ULTRASONIC,HIGH);
  // Calculate the distance using 58 which turns the sound of air
  // from meters per second to cm per microsecond.
  distance=duration/58;
  
  // Return the distance in centimeters
  return distance;
}




// Function to display distance using LEDs
void lightLEDs(int distance) {
  // Check if the object is closer than 25 cm.
  if (distance < MIN_DISTANCE) {
    // Then turn all LEDs on
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], HIGH);
    }
    // Delay for half a second
    delay(500);
    // Turn all LEDs off to get a blinking effect
    for (int i = 0; i < 4; i++) {
      digitalWrite(ledPins[i], LOW);
    }
    // Delay for half a second.
    delay(500);
  } else {
    int litLEDs = map(distance, MAX_DISTANCE, MIN_DISTANCE, 0, 4);
    // For each LED
    for (int i = 0; i < 4; i++) {
      // If the current LED is supposed to be lit up.
      if (i < litLEDs){
        // Light it up
        digitalWrite(ledPins[i], HIGH);
      } 
      // If the current LED is not supposed to be lit up
      else {
        // Turn it off.
        digitalWrite(ledPins[i], LOW);
      }
    }
  }
}


// Function to generate tone based on distance
void generateTone(int distance) {
  // Check if the distance is smaller than the max distance
  if (distance < MAX_DISTANCE) {
    // Calculate frequency based on distance
    int frequency = map(distance, MAX_DISTANCE, MIN_DISTANCE, MIN_TONE, MAX_TONE);
    // Play the sound
    tone(BUZZER, frequency);
  } else {
    // If the object is too far, don't play any sound
    noTone(BUZZER); 
  }
}
