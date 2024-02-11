// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 3
// Exercise 1
// Submission code:

//Main program section

/**
* This program creates a blinking LED.
* 
* Purpose: To blink an LED on the arduino
* DIT632
* 
* 
**/

void setup()
{
  pinMode(2, OUTPUT);
}

void loop()
{
  digitalWrite(2, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(2, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
}