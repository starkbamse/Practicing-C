// (C) Omid Khodaparast, Kaisa Arumeel, Alexander Säfström - Group: 2
// Work package 3 
// Exercise 4
// Submission code: 

#include <Keypad.h> // adding the Keypad value in order to perform keypad functions

const byte row = 4; // Row of size 4
const byte column = 4; //Column of size 4

byte row_pins[row] = {11, 10, 9, 8}; // Define pins for rows
byte column_pins[column] = {7, 6, 5, 4}; // Define pins for columns

// A matrix of keypad characters
char keys[row][column] = { 
  {'1', '2', '3', 'A'}, 
  {'4', '5', '6', 'B'}, 
  {'7','8', '9', 'C'}, 
  {'*', '0', '#', 'D'}
};

// Create a keypad object with the keys and sizes defined.
Keypad keypad = Keypad(makeKeymap(keys), row_pins, column_pins, row, column); 


void setup()
{
  Serial.begin(9600); // start the serial
}

void loop()
{
  // Get the key pressed and store it in a variable
  char keyValue = keypad.getKey(); 

  // If a key has been pressed
  if(keyValue) {
    // Print out the key that was pressed
    Serial.println(keyValue); 
  } 
}
