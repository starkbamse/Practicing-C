// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 4
// Exercise 3
// Submission code: 

//Include section
#include <Adafruit_NeoPixel.h>

//Define section
#define NEOPIXEL 3 // White LED
#define TEMP_SENSOR A0 // Temperature sensor
#define ADC_RESOLUTION 1023.0 // ADC resolution of Arduino
#define MAX_VOLT_MV 5000.0 // Reference voltage
#define LED_COUNT 12
#define RED_LED 4

//Main program section

/**
* This program uses the NeoPixel Ring by Adafruit to light up
* its LEDs when a temperature threshold is reached
* 
* Purpose: To learn about the NeoPixel ring by Adafruit.
* DIT632
*
* https://www.tinkercad.com/things/129X2u8sQOd-wp4e3?sharecode=Wz6VYFzPqRtc9E-Ta01BXaxsfyGDqv69DiONyzqOkE0
* 
**/

Adafruit_NeoPixel ring(LED_COUNT, NEOPIXEL, NEO_RGB);


// Used to get x millivolts from pin y
float getmV(int pin);

// Used to calculate temperature and turn on correct led.
void calcTemp();

int minTemps[]={
  8,16,24,32,40,48,56,64,72,80,88,96,100
};

void setup()
{
  // Set the temperature sensor to be input mode.
  pinMode(TEMP_SENSOR,INPUT);
  
  // Set neopixel to be output mode
  pinMode(NEOPIXEL,OUTPUT);
  
  // Set the red led to be output mode
  pinMode(RED_LED,OUTPUT);
  
  // Begin serial comms at 9600 baud
  Serial.begin(9600);
  
  // Initialize the neopixel ring
  ring.begin();           
  
  // Display the initial values
  ring.show();            
  
  // Set LED brightness to 50%
  ring.setBrightness(50); 

}

void loop(){

  int temp; // Used to store temperature
  int i; // To keep track of where we are in loop.
  int oneNotLit=0; // A switch if a LED is off.
  
  /*
  * TMP36 is designed to output 750mV at 25C.
  * TMP36 increases its mV output by 10mV for every 1C.
  * This means that we can divide mV by 10 to get the degrees.
  * Since 75 differs by a constant of 50 from 25 we subtract this
  * from the result to get the final formula: C=(x/10)-50
  */
  temp=(getmV(TEMP_SENSOR)/10)-50;
  
  // Loop through all the thresholds
  for(i=0;i<(LED_COUNT);i++){
    // If the temperature is greater than min. threshold
    if(temp>=minTemps[i]){    	
      	// Activate blue color on this LED
      	ring.setPixelColor(i, 0,0, 255, 0);
      
        // Display the new color
    	ring.show();
      
      	// Delay for artistic purposes.
      	delay(10);
      	
    } else {
      	oneNotLit=1;
      	// If the temperature is too low, we will turn off
        // the LED on this address.
        ring.setPixelColor(i, 0, 0, 0, 0);
         
      // Delay for artistic purposes.
      	delay(10);
     
        // Update ring state.
    	ring.show();
    }
  }
  
  // If all LEDs are lit
  if(!oneNotLit){
     // Activate the red led
    digitalWrite(RED_LED,HIGH);  
  } else {
    // If at least one LED not, lit. Send LOW signal.
    digitalWrite(RED_LED,LOW);
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
