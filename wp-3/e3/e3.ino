// (C) Omid Khodaparast, Kaisa Arumeel, Alexander Säfström - Group 2 
// Work package 3 
// Exercise 3
// Submission code:


int TEMP_SENSOR_MAX = 1023; // Maximum value of the temperature sensor range.
int temperatureSensorPin = A0; // Define pin for temperature sensor.
const float referenceVoltage = 5000.0; // Arduino reference voltage in millivolts


void setup()
{
  // Initate the serial port
  Serial.begin(9600);
}

// This method executes in an infinite loop
void loop()
{
  // Get the analog reading value for the voltage from the temperature sensor.
  float sensorValue = analogRead(temperatureSensorPin);
  
  //Convert the analog value into millivolts
  float voltage = (sensorValue / TEMP_SENSOR_MAX)*referenceVoltage;
  //Calculate the temperature based on the formula given.
  float temperature = (voltage-500)/10;
  // Print the temperature to the serial output
  Serial.print("Current Temperature in degrees C: ");
  Serial.println(temperature);

  // Add a delay of 500ms
  delay(500);
  
}

