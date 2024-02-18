// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 4
// Exercise 1
// Submission code: xxxxxxx

// Define section
// TIMER1 is 16 MHz, meaning that there are 16,000,000 oscillations per second
// Timers have a pre-scaler which is used to lowe the frequency of the timer. The scale is 1, 8, 64, 256, 1024 for TIMER0 and TIMER1
// We use the 1024 scale which makes the timer to have a frequency of 15.625 KHz.
// We want a frequency of 2 Hz, so that interruptions happen once every half a second. The time interruptions can use a
// compare match value register (so whenever a certain amount of ticks (oscillations) is reached, the interruptions take place) or an
// overflow register. We use the compare match value register in our program. So we want 15.625 KHz to become 2 Hz
// 15625 / (COMPARE_MATCH_VAL + 1) = 2. Note that we add 1 as 0 is a valid value for the tick and we cant have division by 0
// Using math, solving the equation for COMPARE_MATCH_VAL, we get 7811.5 which we round up to 7812 as we cant have floats. 
// This means that the interruption should happen whenever there are 7812 ticks counted by the timer.
#define COMPARE_MATCH_VAL 7812
// Maximum Analog value is 1023. this is used to convert analog readings to digital readings
#define ADC_MAX 1023.0
#define NUM_OF_LEDS 5
// Pin 14 is the same as pin A0
#define TEMP_PIN 14
#define BLUE_LED 12
#define GREEN_LED 9
#define YELLOW_LED 6
#define ORANGE_LED 3
#define RED_LED 2

// --- Type definitions ---
// Struct used to see if LEDs should be turned off or on
typedef struct {
    uint8_t pin;
    uint8_t status;
} LEDStatus;

// Struct that will be used to hold values regarding max and min temp and LEDs that are on or off
typedef struct {
    float minTemp;
    float maxTemp;
    LEDStatus statusOfLEDs[NUM_OF_LEDS];
} Thresholds;
// --- Type definitions ---

// --- Function declaration ---
// Read sensor value and convert it to temperature
float readTemp();
// Turn LEDs on based on temperature
void figureLEDsBasedOnTemp();
// Turns LEDS on. We need the size due to the fact that the array is passed as a pointer and its size cannot be
// Calculated inside the function
void turnLEDsOn(LEDStatus *LEDsStatus);
// --- Function declaration ----

// --- Variable declaration ---
// Volatile variable (since it is changed by the ISR) to hold temperature
volatile float temp;

// This array holds the status of LEDs for mentioned temperatures
// THe last element of the array is used when temperature is not in the intervals defined in earlier elements
Thresholds thresholds[] = {
    {0, 10, {{BLUE_LED, HIGH}, {GREEN_LED, LOW}, {YELLOW_LED, LOW}, {ORANGE_LED, LOW}, {RED_LED, LOW}}},
    {10, 20, {{BLUE_LED, HIGH}, {GREEN_LED, HIGH}, {YELLOW_LED, LOW}, {ORANGE_LED, LOW}, {RED_LED, LOW}}},
    {20, 30, {{BLUE_LED, HIGH}, {GREEN_LED, HIGH}, {YELLOW_LED, HIGH}, {ORANGE_LED, LOW}, {RED_LED, LOW}}},
    {30, 40, {{BLUE_LED, HIGH}, {GREEN_LED, HIGH}, {YELLOW_LED, HIGH}, {ORANGE_LED, HIGH}, {RED_LED, LOW}}},
    {40, 50, {{BLUE_LED, HIGH}, {GREEN_LED, HIGH}, {YELLOW_LED, HIGH}, {ORANGE_LED, HIGH}, {RED_LED, HIGH}}},
    {0, 50, {{BLUE_LED, LOW}, {GREEN_LED, LOW}, {YELLOW_LED, LOW}, {ORANGE_LED, LOW}, {RED_LED, LOW}}}
};
// --- Variable declarations

/**
 * This program uses time interruptions (every 500 ms) to read temperature values from the tmp36 temperature sensor
 * Then based on the temperature that is read and the conditions defined above, a correspondent LED is turned on.
 * The program makes use of TIMER1 to cause the interruptions. The program uses compare match value to trigger the 
 * temperature reading interruptions.
*/

void setup() {
    // Set the pin modes
	pinMode(TEMP_PIN, INPUT);
    pinMode(BLUE_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(YELLOW_LED, OUTPUT);
    pinMode(ORANGE_LED, OUTPUT);
    pinMode(RED_LED, OUTPUT);

    // Now we will initialise timer1 in a way that it woks based on the explanations
    // Given in the comments above. In the mean time we disable interrupts so that the timer 
    // Does not start ticking
    noInterrupts();

    // Initialise timer1 by setting its registers to 0
    TCCR1A = 0;
    TCCR1B = 0;

    // Set the counter value to 0
    TCNT1 = 0;

    // We are using compare match register, we need to set the tick register value to what was calculated
    // in the define section. The timer continuously checks the value of TCNT1 with OCR1A and if they match
    // The interrupt is produced
    OCR1A = COMPARE_MATCH_VAL;

    // We need to use the timer in CTC mode so that we can have customised delays between interrupts
    // This is something we want as we want 500 ms delay between each interrupt
    // To be in CTC mode we need to set the bit corresponding to WGM01 in TCCR1A (which is bit number 1) to 1
    // Shift 1 by the bit number of WGM12 (Which is 1) to the left. THen user the or bitwise operator to set
    // the bit number of WGM01 to 1. Here, we are doing the same as (1 << 1) which gives 0b10
    TCCR1A |= ( 1 << WGM12);

    // Since we are using 1024 pre-scaler, meaning that there will be 15.625 kHz of oscillations per second
    // we need to set the bits CS10 and CS12 to 1 and then apply those bits that are 1 to TCCR1B
    // Here we are doing the same as (1 << 2) | (1 << 0) which gives 0b100 | 0b1 which becomes 0b101
    TCCR1B |= (1 << CS12) | (1 << CS10);

    // Enable compare match value for timer 1 by setting the timer mask's second bit to 1
    // This enables compare match value. Here we are doing the same as (1 << 1) which gives 0b10
    TIMSK1 |= (1 << OCIE1A);

    // Enable interrupts again
    interrupts();
}

void loop() {

}

// THe ISR (Interrupt Service Routine) whenever an interrupt happens, this function si called
ISR(TIMER1_COMPA_vect) {
    // Preload timer with compare match value
    TCNT1 = COMPARE_MATCH_VAL;
    // Read temperature and save it in temp value
    temp = readTemp();
    // Figure what LEDs to turn on afterwards
    figureLEDsBasedOnTemp();
}

float readTemp() {
    // Read the analog value and convert it to volts. Use the tmp36 formula (V - 0.5) * 100 to convert voltage to temp
    // Return the temperature.
    return (((float)analogRead(TEMP_PIN) * 5.0 / ADC_MAX) - 0.5) * 100.0;
}

void figureLEDsBasedOnTemp() {
    // If temperature is not in the interval for the LEDs, then turn all LEDs off
    if (temp < 0 || temp >= 50) {
        turnLEDsOn(thresholds[NUM_OF_LEDS].statusOfLEDs);
        return;
    }

    // Go through the thresholds array and see if temp is between any of the max or min vals 
    // If yes, then turn LEDs on based on status provided for the specific temperature interval
    for (int i = 0; i < (sizeof(thresholds) / sizeof(Thresholds)); i++) {
        if (temp >= thresholds[i].minTemp && temp < thresholds[i].maxTemp) {
            turnLEDsOn(thresholds[i].statusOfLEDs);
            return;
        }
    }
}


void turnLEDsOn(LEDStatus *LEDsStatus) {
    // Go through the status for each LED and based on the status turn them on or off
    for (int i = 0; i < NUM_OF_LEDS; i++) {
        digitalWrite(LEDsStatus[i].pin, LEDsStatus[i].status);
    }
}