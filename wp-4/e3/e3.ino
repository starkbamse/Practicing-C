// (C) Omid Khodaparast, Alexander Säfström, Kaisa Arumeel - Group 2 
// Work package 4
// Exercise 3
// Submission code: 527499


#include <Adafruit_NeoPixel.h> // adding a NeoPixel library for the NeoPixel ring

/*
* This program displays Neopixel LED lights based on the temperature.
* If the temperature is high enough to light all LEDs, another red LED is lit.
*
* Purpose: Neopixel ringlight.
* DIT632
*/

// Define section
#define LED_PIN 6 // NeoPixel ring to pin 6
#define LED 7 // LED to pin 7
#define LIGHTS 12 // Amount of lights in Neopixel ring
#define TEMP_PIN A0 // Temperature pin is A0

// Variable declarations
int TEMP_SENSOR_MAX = 1023; // Maximum value of the temperature sensor range.
const float referenceVoltage = 5000.0; // Arduino reference voltage in volts


// Initialize NeoPixel ring as a strip, assign 12 lights to it, pin number 8 and initialize color bytes
Adafruit_NeoPixel strip(LIGHTS, LED_PIN, NEO_GRB + NEO_KHZ800); 

void setup()
{
  strip.begin(); // Start the NeoPixel ring
  strip.show(); // Display the colors on the ring
}

// This method takes in the amount of lights to light up and lights them up on the Neopixel ring
void fillColors(int amount) { 
  // Loop from 0 until the amount given in parameters
  for(int i = 0; i < amount; i++) { 
    // Set a color on every LED light in NeoPixel
      strip.setPixelColor(i, 64, 156, 255); 
      strip.show(); // Display the colors
    }
  
  // Loop backwards in the rest of the LEDs
   for(int i = 12; i >= amount; i--) { 
     // Set the color of LED to white
      strip.setPixelColor(i, 0, 0, 0); 
      strip.show(); // Display the colors
    }

}

void loop()
{

    // Get the analog reading value for the voltage from the temperature sensor.
    float sensorValue = analogRead(TEMP_PIN);

    //Convert the analog value into voltage(0-5V)
    float voltage = (sensorValue / TEMP_SENSOR_MAX)*referenceVoltage;
    //Calculate the temperature based on the formula given.
    int temperature = (voltage-500)/10;

    // Turn off the red LED.
    digitalWrite(LED, LOW);
    // Check if the temperature is negative
    if(temperature < 0) {
        // Fill one led on the neopixel ring
        fillColors(1);
    } 
    // Check if temperature is between 0 and 10
    else if(temperature >= 0 && temperature < 10) {
         // Fill 3 leds on the neopixel ring
        fillColors(3); 
    } 
    // Check if temperature is between 10 and 20
    else if(temperature >= 10 && temperature < 20) { 
        // Fill 6 leds on the neopixel ring
        fillColors(6); 
    } 
    // Check if temperature is between 20 and 30
    else if(temperature >= 20 && temperature < 30) {
        // Fill 9 leds on the neopixel ring
        fillColors(9);
    } 
     // Check if temperature is over 30
    else if(temperature >= 30) { 
        // Fill all 12 leds on the neopixel ring
        fillColors(12); 
        // Light up the red led
        digitalWrite(LED, HIGH); 
    }

  delay(500); // delay for 0.5 seconds

}