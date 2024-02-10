// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 3
// Exercise 3 (part 1)
// Submission code: xxxxxxx

// Define section
#define TEMP_PIN 14 // A0 pin
#define DELAY_MS 500 // 500 ms of delay used in the program

// --- Function declaration ---
// This function reads the value from temp sensor and turns into Celsisus and returns it
int readTempInCel();
// --- Function declaration ---

/**
 * Note: Arduino is a digital device and cannot read analog values
 * How arduino goes arounf this is that it makes use of Analog to Digital Converter (ADC)
 * It converts the Analog value it reads to a range from 0 to 1023 (inlcuding)
 * 0 is the same as 0 v while 1023 is the same as 5v.
 * This program uses ADC to calculate temperature. Moreover, the temperature is printed
 * on the serial monitor
*/

// steup function, executed once when executable code is flushed on the board
void setup() {
	// Set the temperature pin as INPUT as we get temp values from it
    pinMode(TEMP_PIN, INPUT);

    // Start the serial monitor with 9600 (meaning that it reads 9600 bits per second)
    Serial.begin(9600);
}

// The loop function, executed forever by the Uno. It is basically and infinite loop
void loop() {
    // Print temp on the serial monitor
	Serial.println(readTempInCel());
    // Delay for half a second and then read tem again
    delay(DELAY_MS);

}

int readTempInCel(void) {
    // In order to save memory, we do not create many variables
    // Multiplaying the ADC value read by analog read by 5 and then diiding it by 1023
    // we get the potential difference read.
    // Then using the formula temp = (Vout - 0.5) * 100 we get temp
    return (((float)analogRead(TEMP_PIN) * 5 / 1023.0) - 0.5) * 100;
}