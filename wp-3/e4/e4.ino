#include <Keypad.h>

// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 3
// Exercise 4
// Submission code: xxxxxxx

// Include section
#include <Keypad.h>

// Define section
#define DELAY_MS 500 // 500 ms (aka 0.5 s) of delay

// --- Variable declaration ---
char pressed; // Get the Char that is pressed
uint8_t rowPins[4] = {8, 9, 10, 11}; // Array that saves the pin addresses for the rows starting from row 1 to row 4
uint8_t colPins[4] = {4, 5, 6, 7}; // array that saves the addresses of cols starting from col 1 to col 4
// Matrix that holds the keys at each row-col intersection
char keys[4][4]={
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}};
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, 4, 4); // Keypad object
// The last two argument stand for the number of rows and cols which are 4 and 4
// --- Variable declaration ---

/**
 * This program reads keys that are pressed on akeypad and prints them on the serial monitor
 * Note: The keypad is 4x4 which means there are 16 different outputs (0-F in hex). Row pins are
 * configured as OUTPUT and col pins as INPUT. We use the Keypad.h library to read the key that is
 * pressed
*/

// steup function, executed once when executable code is flushed on the board
void setup() {
    // Set the serial monitor to read 9600 bits per second
    Serial.begin(9600);
}

// The loop function, executed forever by the Uno. It is basically and infinite loop
void loop() {
    // Get the pressed key
    // if no key is pressed '\0' is returned
	pressed = keypad.getKey();
    // If the function returned char '\0', then do not print it
    if (pressed != '\0') {
        Serial.println(pressed);
    }
}
