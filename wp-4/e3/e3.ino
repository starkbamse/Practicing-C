// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 4
// Exercise 1
// Submission code: xxxxxxx

// LINK: https://www.tinkercad.com/things/7RUT4NB2Y0Z-blinkledringbasedontemp?sharecode=wW_j2Y4uWYvd1XhbpnRKoy2ymCBJ6MrsOzft84lsmBU

// Include section
// We use the following library to control the how the LEDs turn off and on
#include <Adafruit_NeoPixel.h>

// Define section
// Needed amount of ticks to make a delay of 500 ms between each interrupt
#define COMPARE_MATCH_VAL 7812
#define ADC_MAX 1023.0
#define NUM_OF_LEDS_ON_RING 12
// THe ring's INPUT pin number
#define RING_PIN_IN_NUM 5
#define MAX_TEMP 60
#define MIN_TEMP 0
#define BLUE_LED_PIN 7
#define RED_LED_PIN 9
#define TEMP_PIN 14

// --- Type definitions ---
// Struct used to keep the colour for th LEDs which are to be coloured
// using the bounds in the first element
typedef struct {
    uint8_t LEDBounds[2];
    uint8_t red;
    uint8_t green;
    uint8_t blue;
} RGB;

// Struct to save the colouring of LEDs for different temperature intervals
typedef struct {
    int minTemp;
    int maxTemp;
    RGB LEDsStatus[NUM_OF_LEDS_ON_RING];
} Thresholds;
// --- Type definitions ---

// --- Function definitions ---
// This method figures which threshold item is to be applied on the LEDs
void figureLEDs();
// Reads temperature inputted by the temperature sensor
float readTemp();
// Turns on LEDs based on the status array provided
void turnLEDOn(RGB *LEDsStatus);
// --- Function declarations ---

// --- Variable declarations ---
// Adafruit_NeoPixel object to be used to modify LED colouring on the NeoPixel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUM_OF_LEDS_ON_RING, RING_PIN_IN_NUM, NEO_GRB + NEO_KHZ800);
// temperature value
volatile float temp;
// List of thresholds that are applied based on the temperature
Thresholds thresholds[] = {
    {0, 10, {{{0, 1}, 0, 0, 255}, {{2, 3}, 0, 0, 0}, {{4, 5}, 0, 0, 0}, {{6, 7}, 0, 0, 0}, {{8, 9}, 0, 0, 0}, {{10, 11}, 0, 0, 0},}},
    {10, 20, {{{0, 1}, 0, 0, 255}, {{2, 3}, 0, 255, 0}, {{4, 5}, 0, 0, 0}, {{6, 7}, 0, 0, 0}, {{8, 9}, 0, 0, 0}, {{10, 11}, 0, 0, 0},}},
    {20, 30, {{{0, 1}, 0, 0, 255}, {{2, 3}, 0, 255, 0}, {{4, 5}, 255, 255, 0}, {{6, 7}, 0, 0, 0}, {{8, 9}, 0, 0, 0}, {{10, 11}, 0, 0, 0},}},
    {30, 40, {{{0, 1}, 0, 0, 255}, {{2, 3}, 0, 255, 0}, {{4, 5}, 255, 255, 0}, {{6, 7}, 255, 132, 0}, {{8, 9}, 0, 0, 0}, {{10, 11}, 0, 0, 0},}},
    {40, 50, {{{0, 1}, 0, 0, 255}, {{2, 3}, 0, 255, 0}, {{4, 5}, 255, 255, 0}, {{6, 7}, 255, 132, 0}, {{8, 9}, 255, 72, 0}, {{10, 11}, 0, 0, 0},}},
    {50, 60, {{{0, 1}, 0, 0, 255}, {{2, 3}, 0, 255, 0}, {{4, 5}, 255, 255, 0}, {{6, 7}, 255, 132, 0}, {{8, 9}, 255, 72, 0}, {{10, 11}, 255, 0, 0},}},
};
// --- Variable declarations ---

/**
 * This program makes use of a NeoPixel ring with 12 LEDs and a temperature sensor.
 * When temperature is read, based on the thresholds defined, a number of LEDs are turned on on the NeoPixel ring
 * With different colouring to indicate different temperature intervals. If the temperature is too cols all NeoPixel ring
 * LEDs are turned blue and a blue LED is also turned on. If the temperature is too hot, all the LEDs on the NeoPixel ring are
 * turned red and a red LED is also tuned on.
*/

// Setup function, where Timer1  and pin-out instructions are set up.
void setup() {
    // Initialise NeoPixel Strip object
	pixels.begin();
    // Set all LEDs off
    pixels.clear();

    // Set the red and blue LED pins as OUTPUT
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(BLUE_LED_PIN, OUTPUT);
    // Disable interrupts while initialising Timer1
    noInterrupts();

    // Set A and B registers to 0
    TCCR1A = 0;
    TCCR1B = 0;
    // Set the clock count to 0
    TCNT1 = 0;
    // Set the required number of ticks for interrupts to happen to COMPARE_MATCH_VAL
    OCR1A = COMPARE_MATCH_VAL;
    // Turn on CTC mode
    TCCR1A |= (1 << WGM12);
    // Set pre-scaler to 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);
    // Set bit 1 of the Timer1 mask to 1 so that interruptions after the specified amount of ticks are enabled
    TIMSK1 |= (1 << OCIE1A);
    // Enable interrupts
    interrupts();
}

void loop() {

}

// Interrupt Routine Service for Timer1
ISR(TIMER1_COMPA_vect) {
    // Read temp
    temp = readTemp();
    // Figure the threshold to use on LEDs based on the temp read
    figureLEDs();
}

float readTemp() {
    // Read the analog value and convert it to volts. Use the tmp36 formula (V - 0.5) * 100 to convert voltage to temp
    // Return the temperature.
    return (((float)analogRead(TEMP_PIN) * 5.0 / ADC_MAX) - 0.5) * 100.0;
}

void figureLEDs() {
    // If temp is less than MIN_TEMP, colour all LEDs in the NeoPixel blue and turn on the blue LED
    // Before that, make sure that the red LED is turned off
    if (temp < MIN_TEMP) {
        // Turn off red LED
        digitalWrite(RED_LED_PIN, LOW);
        // Fill LEDs on the NeoPixel with the blue colour
        // Note that the last LED index provided is not included, so if we have 12 LEDs 
        // and we want to turn them all on, we need to provide number 12 as the last LED, and not 11
        // LEDs are indexed from 0 to 11 on the NeoPixel ring
        pixels.fill(pixels.Color(0, 0, 255), 0, NUM_OF_LEDS_ON_RING);
        // Turn the LEDs on
        pixels.show();
        // Turn on the blue LED
        digitalWrite(BLUE_LED_PIN, HIGH);
        // Exit the function
        return;
    }

    // If the temperature is greater than the MAX_TEMP,
    // Then make all NeoPixel LEDs red, and turn on the red LED
    if (temp >= MAX_TEMP) {
        // First set the blue LED off
        digitalWrite(BLUE_LED_PIN, LOW);
        // Fill LEDs on the NeoPixel with the red colour
        pixels.fill(pixels.Color(255, 0, 0), 0, NUM_OF_LEDS_ON_RING);
        // Turn all NeoPixel LEDs on
        pixels.show();
        // Turn the red LED on
        digitalWrite(RED_LED_PIN, HIGH);
        // Exit the function
        return;
    }

    // Otherwise, the temperature falls between the allowed temps and one of the Thresholds hold true
    // Go through all thresholds and apply the values of the one that matches temperature on the NeoPixel ring LEDs
    for (int i = 0; i < (sizeof(thresholds) / sizeof(Thresholds)); i++) {
        // If temperature is between the min temperature and max temperature, then this threshold should be applied
        if (temp >= thresholds[i].minTemp && temp < thresholds[i].maxTemp) {
            // Before all, make sure that the red and blue LEDs are off
            digitalWrite(BLUE_LED_PIN, LOW);
            digitalWrite(RED_LED_PIN, LOW);
            // Turn on LEDs based on the status the that threshold provides for the NeoPixel ring LEDs
            turnLEDOn(thresholds[i].LEDsStatus);
            // Exit the function
            return;
        }
    }
}

void turnLEDOn(RGB *LEDsStatus) {
    // Since we apply colouring on every two LEDs, meaning that each two LEDs have the same colouring,
    // We go through half the NUM_OF_LEDS_ON_RING on the ring
    for (int i = 0; i < NUM_OF_LEDS_ON_RING / 2; i++) {
        // Go through the RGB values provided for the two LEDs, use the bound 8-bit unsigned ints provided to turn the LEDs
        pixels.fill(pixels.Color(LEDsStatus[i].red, LEDsStatus[i].green, LEDsStatus[i].blue), LEDsStatus[i].LEDBounds[0], LEDsStatus[i].LEDBounds[1] + 1);
    }
    // Turn the LEDs on
    pixels.show();
}