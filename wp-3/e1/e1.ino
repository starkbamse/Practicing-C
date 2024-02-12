// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 3
// Exercise 1
// Submission code: xxxxxxx

// Define section
#define LED_1_PIN 2
#define LED_2_PIN 7
#define PUSHDOWN_B_PIN 11

/**
 * This program makes use of LEDs and a pushdown button.
 * The purpose of the program is to make a LED blink every one sec and
 * use the pushdown button to turn on the other LED.
 * When the button is pressed, the LED is turned on and when it is not pressed
 * the LED is turned off.
*/

int pushBtnVal; // Variable to save input received by pushdown button

// The steup function, executed once when executable code is flushed on the board
void setup() {
    // Set the pin connecting LED 1 to the Uno as OUTPUT
    // This is due to the fact that the Uno will construct when the 
    // LED is to be turned on or turned off
	pinMode(LED_1_PIN, OUTPUT);
    // Set the pin connecting LED 2 to the Uno as OUTPUT
    pinMode(LED_2_PIN, OUTPUT);
    // Set the pin connecting the pushdown button to the uno as INPUT
    // This is due to the fact that we want to read input from the button,
    // aka, when it is pressed, and when it is not pressed
    pinMode(PUSHDOWN_B_PIN, INPUT);
}

// The loop function, executed forever by the Uno. It is basically and infinite loop
void loop() {
    // Read the input received by the pushdown button.
    // Note that the the values received are either 1 (aka HIGH), or 0 (aka LOW)
	pushBtnVal = digitalRead(PUSHDOWN_B_PIN);

    // LED_1 should blink periodocally, every one sec
    // Start by having LED_1 off
    digitalWrite(LED_1_PIN, LOW);

    // Based on the value received from reading the button input
    // If it is HIGH, turn LED_2 on.
    // If not (it is LOW), turn it off
    if (pushBtnVal) {
        digitalWrite(LED_2_PIN, HIGH);
    } else {
        digitalWrite(LED_2_PIN, LOW);
    }
    
    // Delay for one sec, as LED_1 should blink
    // The delay function delays by mili seconds
    // 1000 milli sec = 1 sec
    delay(1000);
    // Turn LED_1 on
    digitalWrite(LED_1_PIN, HIGH);
    // 1000 milli sec = 1 sec
    delay(1000);

    // The next Iteration, we will read button input again
    // Turn off LED_1 and so on
}
