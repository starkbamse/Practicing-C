// (C) Omid Khodaparast, Kaisa Arumeel, Alexander Säfström - Group: 2 
// Work package 4
// Exercise 1 
// Submission code: 

/*
* This program measures the temperature and lids LEDs based on it. You
* E.g. for 0-10 degrees Celsius, 1 LED is turned on; for 11-20, 2 LEDs are turned on, and so on.
* The temperature is checked periodically using interrupts.
*/

#define TEMP_SENSOR_MAX 1023 // Maximum value read from the temperature sensor
#define referenceVoltage 5000 // Reference voltage used for temperature calculations
#define temperaturePin A0 //Pin for the temperature sensor
#define PRESCALER 1024      // Used for calculating speed of timer
#define INTERRUPT_FREQ 1    // Interrupt frequency of 1 second
#define CLOCK_SPEED 16000000// Clock speed of the Arduino Uno


// Function to define which are input and output pins
void setup()
{
  // Clear any interrupts
  cli();
  // Set the IO status of pins 13, 12, 11, 10, 9
  DDRB = B00111110;
  // Set them to low in the beginning
  PORTB = B00000000;
  Serial.begin(9600); // Begin serial
  
  	// Initialise the registers and counter values to 0
    TCCR1A = 0;      
    TCCR1B = 0;
    TCNT1  = 0;      
  	// Calculate the maximum timer value.
  	OCR1A = CLOCK_SPEED / (PRESCALER - INTERRUPT_FREQ);
  
  	// Increment the registers once a second
    TCCR1B |= (1 << WGM12);
    TCCR1B |= (1 << CS12) | (1 << CS10);
    TIMSK1 |= (1 << OCIE1A);
  
  	// Allow the program to have other interrupts.
   	sei();
}


// This method executes in a loop
void loop() {}

// The interrupt service routine runs when the program is interrupted every second.
ISR(TIMER1_COMPA_vect) 
{
  // Clear any other interrupts
  cli();
  
  // Get the analog reading value for the voltage from the temperature sensor.
  float sensorValue = analogRead(temperaturePin);
  
  //Convert the analog value into voltage(0-5V)
  float voltage = (sensorValue / TEMP_SENSOR_MAX)*referenceVoltage;
  //Calculate the temperature based on the formula given.
  int temp = (voltage-500)/10;
  
  // Check if the temperature is between 0 and 10
   if (temp >= 0 && temp <= 10) {
     // Turn on LED 13
  		PORTB = B00100000;
     // Check if the temperature is between 10 and 20
    } else if ((temp > 10) && (temp <= 20)) {
    	PORTB = B00110000;
      	// Turn on LED 13 and 12
     // Check if the temperature is between 20 and 30
    } else if ((temp > 20) && (temp <= 30)) {
     // Turn on LED 13, 12 and 11
    	PORTB = B00111000;
      // Check if the temperature is between 30 and 40
    } else if ((temp > 30) && (temp <= 40)) {
     // Turn on LED 13, 12, 11 and 10
    	PORTB = B00111100;
     // Check if the temperature is over 40
    } else if (temp > 40){
      // Turn on LED 13, 12, 11, 10 and 9
    	PORTB = B00111110;
   } 
  // If the temperature is below 0
  else {
    // Turn all LEDs off
     PORTB = B00000000;
   }

  // Allow other interrupts
	sei();
}
