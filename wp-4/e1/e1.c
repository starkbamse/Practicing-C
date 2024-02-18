// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 4
// Exercise 1
// Submission code: 

//Define section
#define COLDEST 7 // White LED
#define COLDER 6 // Blue LED
#define WARM 5 // Yellow LED
#define WARMER 4 // Orange LED
#define WARMEST 3 // Red LED
#define TEMP_SENSOR A0 // Temperature sensor
#define ADC_RESOLUTION 1023.0 // ADC resolution of Arduino
#define MAX_VOLT_MV 5000.0 // Reference voltage
#define CLOCK_SPEED 16000000.0 // Clock speed of Uno
#define PRESCALER 1024.0 // Prescaler of choice to emulate slow clock
#define SECONDS_INTERVAL 0.5 // Every x seconds to update LEDs

//Main program section

/**
* This program uses Timer interrupts on arduino to light up
* different LEDs depending on the current temperature in
* its environmen.
* 
* Purpose: To learn about timer interrupts and internal
* structure of the Arduino MCU.
* DIT632
*
* https://www.tinkercad.com/things/47gG3Iy8ytA-wp4e1?sharecode=AxyeTj9PibRFon8GgSCVyATOhDdUYbBfXvVlvE8zBRU 
* 
**/

// Used to get x millivolts from pin y
float getmV(int pin);

// Used to calculate temperature and turn on correct led.
void calcTemp();

// Used to define threshold for deviations
typedef struct {
  float minTemp;
  int pin;
} Threshold;

Threshold thresholds[] ={
  {0.0, 7}, // >=0
  {11.0, 6}, // >=11
  {21.0, 5}, // >=21
  {31.0, 4}, // >=31
  {41.0, 3} // >=41
};

void setup()
{
  // Variable declarations
  int i=0; // To keep track of where we are in loop
  float CMR; // To store our Compare Match Register value
  
  // Loop through all thresholds
  for(i=0;i<(sizeof(thresholds)/sizeof(Threshold));i++){
    // Define each led to be on output mode.
    pinMode(thresholds[i].pin,OUTPUT);
  }
  
  // Set the temperature sensor to be input mode.
  pinMode(TEMP_SENSOR,INPUT);
  Serial.begin(9600);
  
  // Clear all previous interrupts.
  cli();
  
  /* 
  * On Arduino Uno timer 0 and timer 2 are 8-bit timers.
  * This means that their max value is 255.
  * Timer 1 is a 16 bit timer, with max value 65535.
  * Using a prescaler we can slow down the clock to get
  * a wanted interval. I want an interval of 500ms therefore
  * I must use the timer 1.
  * 
  * Hz = Clock Speed / Prescaler
  * 
  * To be able to create a timer interrupt, we need to calculate
  * a value that we can put in the compare match register of timer 1.
  * 
  * CMR = ( 16,000,000Hz / (prescaler * desired interrupt frequency) ) - 1
  *	
  * The desired interrupt frequency in this case is 2HZ.
  * 
  * We can calculate Hz by doing 1/x seconds.
  *
  * Prescalers: 256 and 1024 work but since 1024 will use less range in the
  * timer 1 we will use 1024.
  * 
  * We do -1 because the timer's are zero-indexed.
  * 
  * Therefore our CMR value is:
  * 
  * CMR = 7811.5 = ( 16,000,000Hz / (1024 * 2Hz) ) - 1
  * 
  * We will round the value to 7812.
  */
  
  // Calculate the CMR value using above equation.
  CMR = (CLOCK_SPEED / (PRESCALER * (1.0/SECONDS_INTERVAL)))-1.0;
  
  TCCR1A = 0; // Timer Counter Register 1A
  TCCR1B = 0; // Timer Counter Register 1B
  TCNT1 = 0; // Timer Counter 1
  
  // Here we set the CMR value we calculated earlier.
  OCR1A = (int) CMR; // Output Compare Register 1A
  
  // The timer counter register 1b holds information
  // about which mode to use with the timer.
  // We want to use CTC mode that clears the timer when
  // the TCNT1 value matches our OCR1A value.
  // We use bitwise OR to set the WGM12 bit to true.
  TCCR1B = TCCR1B | (1 << WGM12);
  
  // Activating CS12 and CS10 yields in a prescale value of 1024.
  TCCR1B = TCCR1B | (1 << CS12) | (1 << CS10); 
  
  // Activating OCIE1A on TIMSK1 means:
  // that we enable the Output Compare A Match Interrupt Enable.
  // This means that an interrupt will be created whenever the timer
  // value in TCNT1 matches  the OCR1A Value.
  TIMSK1 = TIMSK1 | (1<<OCIE1A); // Timer Interrupt Mask Register 1
	
  // Calling sei() allows the MCU to react to any
  // configured interrupt sources.
  sei();

}

void loop(){}

// Interrupt Service Routine on Timer1 Compare Match A
// Whent the value of TCNT1 matches the OCR1A value,
// the mcu looks in the interrupt vector table. There
// it will be able to find the address of the function/ISR to execute.
// We do not have to worry about placing the function address,
// as this is done by the linker, a tool in compilation that aids
// in placing and populating information in the correct places.
ISR(TIMER1_COMPA_vect) {
  // The following code is the "vector"/address that will be called. 
  int temp; // Used to store temperature
  int i; // To keep track of where we are in loop.
  
  /*
  * TMP36 is designed to output 750mV at 25C.
  * TMP36 increases its mV output by 10mV for every 1C.
  * This means that we can divide mV by 10 to get the degrees.
  * Since 75 differs by a constant of 50 from 25 we subtract this
  * from the result to get the final formula: C=(x/10)-50
  */
  temp=(getmV(TEMP_SENSOR)/10)-50;
  
  // Loop through all the thresholds
  for(i=0;i<(sizeof(thresholds)/sizeof(Threshold));i++){
    // If the temperature is greater than min. threshold
    if(temp>=thresholds[i].minTemp){
      	// We can light up the LED by sending HIGH signal
    	digitalWrite(thresholds[i].pin,HIGH);
    } else {
      	// If the temperature is too low, we will turn off
        // the LED for this pin.
        digitalWrite(thresholds[i].pin,LOW);
    }
  }
}

float getmV(int pin){
  int ADCCount; // The digital representation of analog value
  float mV; // The millivolts

  ADCCount=analogRead(pin); // Read adc count
  
  // Convert the adc count to millivolt by doing
  // (ADCCount/ADCResolution) * Reference voltage
  // Example: (700 ADCc /1023 ADCr) * 5000 mV = 3417 mV
  mV=(ADCCount/ADC_RESOLUTION)*MAX_VOLT_MV;
  
  // Return millivolts
  return mV;
}
