// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 3
// Exercise 3 (part 2)
// Submission code: xxxxxxx

// Define section
#define ROW_1_PIN 8
#define ROW_2_PIN 9
#define ROW_3_PIN 10
#define ROW_4_PIN 11
#define COL_1_PIN 4
#define COL_2_PIN 5
#define COL_3_PIN 6
#define COL_4_PIN 7
#define ROW_0_DIFF 8 // Difference between the row number and number 0
#define COL_0_DIFF 4 // Difference between the col number and number 0
#define DELAY_MS 500 // 500 ms (aka 0.5 sec) delay

// --- Function declaration ---
// This function returns true (1) or false (0) if a key is pressed
int isKeyPressed(void);
// --- Function declaration ---

// --- Variable declaration ---
char pressedKey; // Holds the key value that is pressed by the user
// Change it into a char pointer if you want to make a buffer
uint8_t row; // Variable to go over rows in for loop
uint8_t col; // Variable to go over cols in for loop
// Matrix that holds the keys at each row-col intersection
char keys[4][4]={
 {'1','2','3','A'},
 {'4','5','6','B'},
 {'7','8','9','C'},
 {'*','0','#','D'}};
// --- Variable declaration ---

/**
 * This program reads keys that are pressed on akeypad and prints them on the serial monitor
 * Note: The keypad is 4x4 whihc means there are 16 different outputs (0-F in hex). Row pins are
 * configured as OUTPUT and col pins as INPUT. USing digitalRead() we get col values and using 
 * digitalWrite() we set row values. If a row and a col are both 0, then that key is pressed.
 * Otherwise the key in unpressed.
*/

void setup() {
    // Set the row digital pins as OUTPUT
	pinMode(ROW_1_PIN, OUTPUT);
    pinMode(ROW_2_PIN, OUTPUT);
    pinMode(ROW_3_PIN, OUTPUT);
    pinMode(ROW_4_PIN, OUTPUT);
    // Set the col digital pins as INPUT
    pinMode(COL_1_PIN, INPUT);
    pinMode(COL_2_PIN, INPUT);
    pinMode(COL_3_PIN, INPUT);
    pinMode(COL_4_PIN, INPUT);
    // Configure the serial monitor on transferring 9600 bits per second
    Serial.begin(9600);

    // Set all rows to HIGH
    digitalWrite(ROW_1_PIN, HIGH);
    digitalWrite(ROW_2_PIN, HIGH);
    digitalWrite(ROW_3_PIN, HIGH);
    digitalWrite(ROW_4_PIN, HIGH);
}

void loop() {
    // If a key is pressed, print it to the serial monitor
    if (isKeyPressed()) {
        Serial.println(pressedKey);
    }
    // Delay for DELY_MS milie seconds
    delay(DELAY_MS);
}

int isKeyPressed(void) {
    // The row pins are 8 to 11 as mentioned in the define section
    // Go through each row, set it to LOW first, check each col for the row
    for (row = ROW_1_PIN; row <= ROW_4_PIN; row++) {
        // Set the row to LOW
        digitalWrite(row, LOW);
        for (col = COL_1_PIN; col <= COL_4_PIN; col++) {
            // Serial.print("Row: ");
          	// Serial.println(row - ROW_1_PIN);
          	// Serial.print("Col: ");
          	// Serial.println(col - COL_1_PIN);
            // If the col returns 0, then th ekey is pressed. save the key value, and return 1 to indicate true
            if (!digitalRead(col)) {
                // Serial.println(col - COL_1_PIN);
      	    	pressedKey = keys[row - ROW_0_DIFF][col - COL_0_DIFF];
                // Set the row back to HIGH
                digitalWrite(row, HIGH);
              	return 1;
            }
        }
        // Set the row back to HIGH
        digitalWrite(row, HIGH);
    }

    // No key was pressed, return 0
    return 0;
}
