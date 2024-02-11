// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 3
// Exercise 4
// Submission code:


//Include section
#include <Keypad.h>

// Define section
#define ROWS 4
#define COLS 4

// Main program section

/**
* This program parses a 4x4 matrix keypad using the keypad.h
* library.
* 
* Purpose: To receive input from a keypad using an arduino.
* DIT632
* 
**/

// Create 2d array of keys 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Define which rows are connected to which pins
byte rowPins[ROWS] = { 11, 10, 9, 8 };

// Which cols are connected to which pin
byte colPins[COLS] = { 7, 6, 5,4 }; 

// Create instance of the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


void setup()
{
  // Begin serial communication at 9600 baud.
  Serial.begin(9600);
}

void loop()
{
  // Variable declarations
  char key=kpd.getKey(); // Check if a key is pressed
  
  // If its a valid key
  if(key){
    // Cast the int to char, and print to serial.
  	Serial.println(key);
  }
  
  // As per the documentation of keypad.h
  // delays make the keypad very unresponsive.
}

