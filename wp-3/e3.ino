// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 3
// Exercise 3
// Submission code:

// Define section
#define ADC_RESOLUTION 1024.0 // ADC Resolution of 10 bit
#define MAX_VOLT_MV 5000.0 // Reference voltage
#define RED 2 // Red led
#define GREEN 3 // Green led
#define BLUE 4 // Blue led
#define TEMP_SENSOR A0 // Temperature sensor
#define LIGHT_SENSOR A1 // Light sensor
#define PERIODICITY 500 // Interval of scanning

//Main program section

/**
* This program measures the deviance of light and temperature
* in accordance with predefined intervals. It signals
* the deviances either with green (OK), red (TOO HOT),
* blue (TOO COLD).
* 
* Purpose: To monitor the relationship between temperature
* and light.
* DIT632
*
* Design: https://www.tinkercad.com/things/8rlVARXvi2E-wp3e3dit633?sharecode=755llqPW5Ph0jcfANIKEEX4ZpnBk_y3lRN-X_dbpKP8
* 
**/


// Used to get x millivolts from pin y
float getmV(int pin);

// Used to define threshold for deviations
typedef struct {
  float minTemp;
  float maxTemp;
  float minLight;
  float maxLight;
} Threshold;

Threshold thresholds[] ={
  {-273.0, -11.0, 0.0, 0.0}, //<=-12 0%,0%
  {-12.0 , 0.0, 1.0, 20.0}, //-12C 0C 1% 20% 
  {0.0, 20.0, 21.0, 60.0}, //0C 20C 21%-60&
  {21.0, 999.0, 61.0, 100.0}, //>=21C 61%-100%
};

void setup()
{
  // Set temperature sensor to input mode
  pinMode(TEMP_SENSOR, INPUT);
  // Set light sensor to input mode
  pinMode(LIGHT_SENSOR, INPUT);
  
  // Set green led to output mode
  pinMode(GREEN,OUTPUT);
  
  // Set red led to output mode
  pinMode(RED,OUTPUT);
  
  // Set blue led to output mode
  pinMode(BLUE,OUTPUT);
  
  // Start serial communication at 9600 baud
  Serial.begin(9600);
}

void loop()
{
  // Variable declarations
  int ADCCount=0; // Current ADC count emitted by arduino
  float light=0; // Perceived light
  float temp=0; // Perceived temperature
  int minTemp=0; // Threshold for minimum temperature
  int maxTemp=0; // Threshold for maximum temperature
  int i=0; // To keep track of where we are in loop
  
  /*
  * TMP36 is designed to output 750mV at 25C.
  * TMP36 increases its mV output by 10mV for every 1C.
  * This means that we can divide mV by 10 to get the degrees.
  * Since 75 differs by a constant of 50 from 25 we subtract this
  * from the result to get the final formula: C=(x/10)-50
  */
  temp=(getmV(TEMP_SENSOR)/10)-50;
	
  /**
  * After empirical studies it was discovered,
  * that the relationship between the ADC output from the
  * light sensor and the observed light, is not linear.
  * This was done by plotting the minimum and maximum ADC values
  * outputted by the light sensor on a graphing tool.
  * After some experimentation, a relationship was discovered
  * that Voltage/Slider position (%) = ADC Count.
  * From this we could derive that Voltage / ADC Count = Slider position (%)
  * which is the formula used in our program.
  * We took the minimum and maximum for these values,
  * and rescaled them to fit from 0 to 100.
  */
  light=map(MAX_VOLT_MV/analogRead(LIGHT_SENSOR),5.16,100.0,0.0,100.0);
 
  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println("");
  
  // Loop through all the thresholds
  for(i=0;i<(sizeof(thresholds)/sizeof(Threshold));i++){
    
    // If the perceived light is within a valid threshold
    // interval
    if(light<=thresholds[i].maxLight 
       && light>=thresholds[i].minLight){
	
      // If the perceived temperature is too hot
      if(temp>thresholds[i].maxTemp){
        // Send high signal to red led
        digitalWrite(RED,HIGH); 
        // Send low signal to green led
        digitalWrite(GREEN,LOW); 
        // Send low signal to blue led
        digitalWrite(BLUE,LOW);
        break;
      
        // If the perceived temperature is too low
      } else if(temp<thresholds[i].minTemp){
        // Send low signal to red led
        digitalWrite(RED,LOW); 
        // Send low signal to green led
        digitalWrite(GREEN,LOW); 
        // Send high signal to blue led
        digitalWrite(BLUE,HIGH); 
        break;
      } else {
        // If the perceived temperature is within valid
        // interval
        
        // Send low signal to red led
         digitalWrite(RED,LOW); 
        // Send high signal to green led
          digitalWrite(GREEN,HIGH); 
        // Send low signal to blue led
          digitalWrite(BLUE,LOW); 
        break;
      }

      
    }
  }
  
  delay(PERIODICITY); // Wait for 1000 millisecond(s)
}

float getmV(int pin){
  int ADCCount; // The digital representation of analog value
  float mV; // The millivolts

  ADCCount=analogRead(pin); // Read adc count
  
  // Convert the adc count to millivolt by doing
  // (ADCCount/ADCResolution) * Reference voltage
  // Example: (700 ADCc /1024 ADCr) * 5000 mV = 3417 mV
  mV=(ADCCount/ADC_RESOLUTION)*MAX_VOLT_MV;
  
  // Return millivolts
  return mV;
}