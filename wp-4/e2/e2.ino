// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 4
// Exercise 2
// Submission code: 

//Define section
#define SERVO 3 // Servo motor
#define SERVO_PULSE_DURATION 50000 // 20ms in microseconds
#define ADC_RESOLUTION 1023.0 // ADC resolution of Arduino
#define MAX_VOLT_MV 5000.0 // Reference voltage
#define CLOCK_SPEED 16000000.0 // Clock speed of Uno
#define PRESCALER 1024.0 // Prescaler of choice to emulate slow clock
#define SECONDS_INTERVAL 0.02 // Every x seconds to run ISR
#define MIN_PULSE 544 // Minimum pulse length for servo
#define MAX_PULSE 2400 // Maximum pulse length for servo
#define TIMER_VALUE_SECONDS 5 // Start timer from value
#define SERVO_MAX_DEGREE 180.0 // Maximum degree turn of servo
#define TIMER_SECONDS 60
//Main program section

/**
* This program uses Timer interrupts on arduino to control
* a servo motor and simultaneously act as a timer.
* 
* Purpose: To learn about timer interrupts and internal
* structure of the Arduino MCU.
* DIT632
* 
**/

// Used to convert a wanted angle to an electrical pulse
int angleToPulse(float angle);

// A wrapper function to move the servo to a wanted degree
void goTo(float angle);

// Number of seconds left in the timer
volatile int timeLeft=TIMER_SECONDS;

// Number of fractions of a second.
volatile int secondFractions=0;
  
void setup()
{
  // Variable declarations
  int i=0; // To keep track of where we are in loop
  float CMR; // To store our Compare Match Register value
  

  // Set the temperature sensor to be input mode.
  pinMode(SERVO,OUTPUT);
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
// the mcu looks in the interrupt vector (address) table. There
// it will be able to find the address of the function/ISR to execute.
// We do not have to worry about placing the function address,
// as this is done by the linker, a tool in compilation that aids
// in placing and populating information in the correct places.
ISR(TIMER1_COMPA_vect) {

  /**
  * This code is called at a rate of 50Hz,
  * which is according to the specifications of the 
  * servo motor. However since we also need to print
  * the number of seconds, we will need to create a separate
  * counter for that within our ISR. We split a second into
  * so-called second fractions. The number of second fractions
  * depend on the servo's refresh rate. As mentioned, 50 hz.
  * Which in this case results in 50 second fractions
  */
 
  
  // Map the amount of time left to a degree for the servo
  // After that call goTo to move the servo
  goTo(map(timeLeft,TIMER_SECONDS,0,0,180));
  
  // If the number of secondFractions is 50 (50 hz) and time >0
  if((secondFractions>=(1000/(1000*SECONDS_INTERVAL)))
    && timeLeft>=0){
    // Reset the fraction counter
    secondFractions=0;
    // Print the timer.
    Serial.println(timeLeft);
    // Decrement a second from the timer
    timeLeft--;

  }
  
  // Increment the number of fractions
  secondFractions++;
}

void goTo(float angle) {
    //Set servo pin to high
    digitalWrite(SERVO, HIGH);
  	
    // Convert the degrees into a pulse (duration)
  	int pulse=angleToPulse(angle);
  	
    //Delay and generate a pulse
    delayMicroseconds(pulse); 

    //End the pulse
    digitalWrite(SERVO, LOW);

  	// Wait for some time before starting a new pulse.
    delayMicroseconds(SERVO_PULSE_DURATION - pulse);
}

int angleToPulse(float angle){
  	// Map a degree 0-100 to the minimum pulse value
    // and maximum pulse value of the servo motor.
	float pulse=map(angle,0.0,180.0,MIN_PULSE,MAX_PULSE);
    return (int)pulse;
}	
