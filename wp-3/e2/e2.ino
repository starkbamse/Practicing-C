// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 3
// Exercise 2
// Submission code: xxxxxxx

// Define section
#define DELAY_MS 1500 // 1.5 sec of delay
#define TEMP_PIN 14 // A0 is pin 14
#define LDR_PIN 15 // A1 is pin 15
#define RED_PIN 7
#define BLUE_PIN 2
#define GREEN_PIN 4

// --- Function declaration ---
// This function reads the value from temp sensor and turns into Celsisus and returns it
int readTempInCel();
// This function returns a percentage of light it is receiving
int readLightInten();
// Indicate correspondence between inputted temp and light intensity
void turnWarningLights(int temp, int lightInten);
// --- Function declaration ---

/**
 * Note: Arduino is a digital device and cannot read analog values
 * How arduino goes arounf this is that it makes use of Analog to Digital Converter (ADC)
 * It converts the Analog value it reads to a range from 0 to 1023 (inlcuding)
 * 0 is the same as 0 v while 1023 is the same as 5v
 * This program gets temp value from the environment as well as light intensity
 * Based on the values, it checks if temp corresponds to light intensity
 * It turns different lights on: Green means the temp corresponds to light intensity
 * Red means that temp is higher than what light intensity indicates
 * Blue means temp is lower than what light intensity indicates
*/

// The steup function, executed once when executable code is flushed on the board
void setup() {
    // Temprature and LDR sensors send data, so their pins are configured as INPUT
	pinMode(TEMP_PIN, INPUT);
    pinMode(LDR_PIN, INPUT);

    // Based on Temp and light intensity data we turn LEDs on, so they are configured as OUTPUT
    pinMode(RED_PIN, OUTPUT);
    pinMode(BLUE_PIN, OUTPUT);
    pinMode(GREEN_PIN, OUTPUT);
}

// The loop function, executed forever by the Uno. It is basically and infinite loop
void loop() {
    // Read temperature and light intensity from the sensors and turn LEDs on based on their value
    turnWarningLights(readTempInCel(), readLightInten());
    // Read based on the delay defined in the beginning
    delay(DELAY_MS);
}

int readTempInCel(void) {
    // In order to save memory, we do not create many variables
    // Multiplaying the ADC value read by analog read by 5 and then diiding it by 1023
    // we get the potential difference read.
    // Then using the formula temp = (Vout - 0.5) * 100 we get temp
    return (((float)analogRead(TEMP_PIN) * 5 / 1023.0) - 0.5) * 100;
}

int readLightInten(void) {
    // We want to get light intensity percentage, 1023 corresponds to 100%
    // Hence, we divide the value read by the input by 1023 and then multiply by 100 and truncate
    // This will be the percentage of light intensity
    return (analogRead(LDR_PIN) / 1023) * 100;
}

void turnWarningLights(int temp, int lightInten) {
    // Check for light intensity 0 and different tempratures
    // If temp is less than -12 and light intensity is 0, turn on greed LED 
    // and turn off the rest 
    if (lightInten == 0 && temp < -12) {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);
    // If temp is greater than or equal to -12, turn red LED on
    } else if (lightInten == 0 && temp >= -12){
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(RED_PIN, HIGH);
    // If temp is less then -12 and light inten is greater than 0, turn blue LED on
    } else if (lightInten > 0 && temp < -12){
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
    // If temp is between -12 and 0 and lightInten between 0 and 20, turn on green LED
    } else if (lightInten > 0 && lightInten <= 20 & temp >= -12 && temp <= 0) {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);
    // If lightInten is between 0 and 20 and temp is greater than 0, turn on red LED
    } else if (lightInten > 0 && lightInten <= 20 && temp > 0) {
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(RED_PIN, HIGH);
    // If temp is less than or equal to 0 and lightInten is greater than 20, turn on blue LED
    } else if (lightInten > 20 && temp <= 0) {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
    // If lightInten is between 20 and 60 and temp between 0 and 20, turn green light on
    } else if (lightInten > 20 && lightInten <= 60 && temp > 0 && temp <= 20) {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);
    // If lightInten is between 0 and 60 and temp higher than 20, turn red light on
    } else if (lightInten > 20 && lightInten <= 60 && temp > 20) {
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(RED_PIN, HIGH);
    // If lightInten is greater than 60 and temp less than 20, turn blue light on
    } else if (lightInten > 60 && temp <= 20) {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, HIGH);
    // If lightInten is greater than 60 and temp is greater than 20, turn green on
    } else {
        digitalWrite(RED_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(GREEN_PIN, HIGH);
    }
}