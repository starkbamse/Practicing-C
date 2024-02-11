// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 3
// Exercise 1
// Submission code:

// Define section
#define R1 11 // Row 1
#define R2 10 // Row 2
#define R3 9 // Row 3
#define R4 8 // Row 4
#define C1 7 // Column 1
#define C2 6 // Column 2
#define C3 5 // Column 3
#define C4 4 // Column 4

// Main program section

/**
* This program parses a keypad using a 4x4 matrix.
* The default state for the columns is HIGH, and the
* rows too. The loop sets one of the ROWS to LOW,
* effectively 0V, grounding that particular row. 
* Then, we loop through all the columns.
* If any of them are also LOW, it means that a button has
* been pressed. This is because of the keypad's circuit design
* which creates a controlled path between a HIGH state and a 
* LOW state when a button is pressed, resulting in an overall
* LOW state because there no longer exists a potential difference.
* 
* Purpose: To receive input from a keypad using an arduino.
* DIT632
* 
* Design: https://www.tinkercad.com/things/jdMRdh80S7I-wp3e3keyboarddit633?sharecode=x0vdyAv7zGjYH0d6l1xbQisLQw_efdj8qv3SL73Jx2E
*
**/

// Used to map a row and col combination to a char.
typedef struct {
  char character;
  int row;
  int col;
} keyMap;

// A map of the keys and their row and col values.
keyMap keys[]={
  {'1',R1,C1},
  {'2',R1,C2},
  {'3',R1,C3},
  {'A',R1,C4},
  {'4',R2,C1},
  {'5',R2,C2},
  {'6',R2,C3},
  {'B',R2,C4},
  {'7',R3,C1},
  {'8',R3,C2},
  {'9',R3,C3},
  {'C',R3,C4},
  {'*',R4,C1},
  {'0',R4,C2},
  {'#',R4,C3},
  {'D',R4,C4},
};



// Used to parse which key has been pressed on the keyboard
int getKeyPressed();

void setup()
{
  // Variable declarations
  int i; // Used to track where we are in loop
  
  // Program logic
  
  // Loop through all the rows
  for(i=R4;i<=R1;i++){
    // Set current row to output
  	pinMode(i,OUTPUT);
    
    // Send HIGH state to digital pin
    digitalWrite(i,HIGH);
  }
  
  // Loop through all columns
  for(i=C4;i<=C1;i++){
    // Set current column to input
  	pinMode(i,INPUT);
  }
  
  // Begin serial communication at 9600 baud.
  Serial.begin(9600);
}

void loop()
{
  // Variable declarations
  int key=getKeyPressed(); // Check if a key is pressed
  
  // If not -1, there is a key press.
  if(key!=-1){
    // Cast the int to char, and print to serial.
  	Serial.println((char) key);
  }
  
  // Delay by 1000.
  delay(1000);
}

int getKeyPressed(){

  
  int i; // Keeps track of where we are in loop of rows
  int x; // Keeps track of where we are in loop of columns
  int y; // Keepts track of where we are in loop of keys
  // Loop through all rows
  for(i=R4;i<=R1;i++){
    
    // Ground current row
   	digitalWrite(i,LOW); 
    
    // Loop through all columns
    for(int x=C4;x<=C1;x++){
      
      // If column is also grounded
      if(digitalRead(x)==LOW){
        
        // Find out which key is pressed
        for(int y=0;y<(sizeof(keys)/sizeof(keyMap));y++){
          
          // If a match is found
          if(keys[y].row==i && keys[y].col==x){
            
              // Return the int representation of the char
              return (int) keys[y].character;
          }
        }
      }
    }
    
    // Reset to default state
    digitalWrite(i,HIGH);
  }
  
  // In case nothing is found, we return -1
  return -1;
}