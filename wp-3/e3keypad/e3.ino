// (C) Omid Khodaparast, Kaisa Arumeel, Alexander Säfström - Group: 2
// Work package 3 
// Exercise 3 keypad
// Submission code: 


const byte row = 4; // Row of size 4
const byte column = 4; //Column of size 5

byte row_pins[row] = {11, 10, 9, 8}; // Define pins for the rows
byte column_pins[column] = {7, 6, 5, 4}; // Define pins for the columns

// Create a matrix consisting of keypad characters.
char keys[row][column] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7','8', '9', 'C'},
  {'*', '0', '#', 'D'} 
};


// Method to initialise the pins and start the serial
void setup()
{
  Serial.begin(9600); // start the serial

  // For each item in a row or column
  for(int i = 0; i < 4; i++) {
	pinMode(row_pins[i], OUTPUT); // Assign row pins as output pins
    pinMode(column_pins[i], INPUT); // Assign column pins as input
  }
}

// This method loops forever
void loop()
{
 
  for(int i = 0; i < 4; i++) { // For each iterm in a row
    digitalWrite(row_pins[i], LOW); // Turn off the circuit for row pins
    for(int j = 0; j < 4; j++) { // For each item in a column
      // If a button has been pressed on a particular position from column pin
      if(digitalRead(column_pins[j]) == LOW) { 
        // Print out the current character from the matrix.
        Serial.println(keys[i][j]); 
        // Delay for half a second
        delay(500);
      }
    }
    // Turn the flow of circuit on for the current row pin.
    digitalWrite(row_pins[i], HIGH);
  }
  
}

