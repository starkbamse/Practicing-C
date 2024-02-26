// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 6
// Exercise 2
// Submission code: xxxxxx

// Define section
#define ULTRASONIC_PIN 7
#define PIEZO_PIN 9
#define LED_1_PIN 2
#define LED_2_PIN 3
#define LED_3_PIN 4
#define LED_4_PIN 5
#define MX_DIST 250
#define MIN_DIST 0
#define SPEED_OF_SOUND_IN_AIR 341.0
#define LOWEST_FREQ 50
#define HIGHEST_FREQ 4000
#define HIGHEST_DISTANCE 250
#define LOWEST_DISTANCE 0
#define NOISE_DURATION 10 // Milli sec

// --- Type defintions ---
// Struct used to see how many LEDs should be turned on
// It holds a distance interval, e.g. 150 to 200 cm
typedef struct {
    int upperBoundDist;
    uint8_t LEDPin;
} Threshold;
// --- Type defintions ---

// --- Function declarations ---
// Gets input from the ultrasonic sensor and calculates distance
void calcObjDistance();
// Makes harsher noises the closer the distance gets
void makeNoise(int distance);
// Turns LEDs on base on the distance provided
void turnLEDsOn(int distance);
// --- Function declarations ---

// --- Variable declarations ---
// Thresholds whihc indicate how close an object should be for different number of LEDs to turn on
Threshold thresholds[] = {
    {200, LED_1_PIN},
    {150, LED_2_PIN},
    {100, LED_3_PIN},
    {30, LED_4_PIN}
};
int distance; // Holds the distance of the object in centimeters
// --- Variable declarations ---

/**
 * This program makes use of a Piezo, and ultrasonic sensor and four LEDs to build a parking
 * sensor. The ultrasonic sensor measures distance by sending pings for small periods of time.
 * The Piezo, based on the distance of the object identified, makes noises with different frequencies.
 * The close the object, the higher thr frequency. Moreover, there are four LEDs which are turned on the closer
 * the object gets
*/

// Setup function, where code runs only once
void setup() {
    // Set the pin modes of the LEDs
	pinMode(LED_1_PIN, OUTPUT);
    pinMode(LED_2_PIN, OUTPUT);
    pinMode(LED_3_PIN, OUTPUT);
    pinMode(LED_4_PIN, OUTPUT);
}

// Loop function, where the cod eis periodically executed
void loop() {
	calcObjDistance();
    turnLEDsOn(distance);
    makeNoise(distance);
    delay(10);
}

void calcObjDistance() {
    int time; // Variable to save the time taken for the echo to be sent and received
    // Set the the signal pin for ultrasonic sensor to OUTPUT
    pinMode(ULTRASONIC_PIN, OUTPUT);
    // Clear the system
    digitalWrite(ULTRASONIC_PIN, LOW);
    // Wait for 2 milli sec
    delay(2);
    // Send a ping
    digitalWrite(ULTRASONIC_PIN, HIGH);
    // Wait for 10 milli sec
    delay(10);
    // Stop sending pings by setting the pin to OUTPUT
    digitalWrite(ULTRASONIC_PIN, LOW);
    // Change to input to receive the echo
    pinMode(ULTRASONIC_PIN, INPUT);
    // See how long did it take for the pulse to go and come back
    // Time is in microseconds
    time = pulseIn(ULTRASONIC_PIN, HIGH);

    // Sound speed in air = distance / time -> distance = time * sound speed in air
    // multiply by 100 (we want cm). Sound speed is 341 m/S. Divide by 1000000 (we want time in s).
    // This did not work on TinkerCad
    // distance = (float)time * SPEED_OF_SOUND_IN_AIR / 10000.0;
    // So I used the constant that TinkerCad uses
    distance = 0.01723 * (float)time;

    // If distance is greater than 250 cm, set it to 250
    if (distance > 250) {
        distance = 250;
    }
}

void makeNoise(int distance) {
    int frequency; // the frequency of the tone

    // We want higher frequency for close distance, so we map the greatest distance to the lowest frequency
    // and smallest distance to highest frequency
    frequency = map(distance, HIGHEST_DISTANCE, LOWEST_DISTANCE, LOWEST_FREQ, HIGHEST_FREQ);
    tone(PIEZO_PIN, frequency, NOISE_DURATION);
}

void turnLEDsOn(int distance) {
    // Go through the thresholds
    // if distance falls between any of the intervals
    // Turn on corresponding LEDs
    // Otherwise, turn them off
    for (int i = 0; i < (sizeof(thresholds) / sizeof(Threshold)); i++) {
        if (distance < thresholds[i].upperBoundDist) {
            digitalWrite(thresholds[i].LEDPin, HIGH);
        } else {
            digitalWrite(thresholds[i].LEDPin, LOW);
        }
    }
}
