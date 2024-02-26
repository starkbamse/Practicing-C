// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 5
// Exercise 3
// Submission code: 384024

// Define section
#define ADC_RESOLUTION 1023.0 // ADC Resolution of 10 bit
#define MAX_VOLT_MV 5000.0    // Reference voltage
#define RED 2                 // Red led
#define GREEN 3               // Green led
#define BLUE 4                // Blue led
#define TEMP_SENSOR A0        // Temperature sensor
#define LIGHT_SENSOR A1       // Light sensor
#define PERIODICITY 1000      // Interval of scanning

// Main program section

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

Threshold thresholds[] = {
    {-273.0, -11.0, 0.0, 0.0},  //<=-12 0%,0%
    {-12.0, 0.0, 1.0, 20.0},    //-12C 0C 1% 20%
    {0.0, 20.0, 21.0, 60.0},    // 0C 20C 21%-60&
    {21.0, 999.0, 61.0, 100.0}, //>=21C 61%-100%
};

volatile float R1 = 10000; // value of R1 on board
volatile float logR2, R2, T;
volatile float c1 = 0.001129148, c2 = 0.000234125,
               c3 =
                   0.0000000876741; // steinhart-hart coeficients for thermistor

void setup() {
  // Set temperature sensor to input mode
  pinMode(TEMP_SENSOR, INPUT);
  // Set light sensor to input mode
  pinMode(LIGHT_SENSOR, INPUT);

  // Set green led to output mode
  pinMode(GREEN, OUTPUT);

  // Set red led to output mode
  pinMode(RED, OUTPUT);

  // Set blue led to output mode
  pinMode(BLUE, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  // Variable declarations
  int ADCCount = 0; // Current ADC count emitted by arduino
  float light = 0;  // Perceived light
  float temp = 0;   // Perceived temperature
  int minTemp = 0;  // Threshold for minimum temperature
  int maxTemp = 0;  // Threshold for maximum temperature
  int i = 0;        // To keep track of where we are in loop

  // The following code is the "vector"/address that will be called.
  int ADC_COUNT = ADC_RESOLUTION - analogRead(TEMP_SENSOR);

  /**
   * Here we are utilizing a formula from a tutorial online:
   * http://sin.lyceeleyguescouffignal.fr/make-an-arduino-temperature-sensor-thermistor-tutorial
   * The parts that we used were the calculation of the resistance of the
   * thermistor, and the conversion of the resistance to temperature in Kelvin.
   * Then we subtract 273.15, the lowest value in celsius in Kelvin to convert
   * the temperature to Celsius.
   */

  // Calculate the resistance of the thermistor
  R2 = R1 * (ADC_RESOLUTION / (float)ADC_COUNT - 1.0);

  // The logarithm of the resistance
  logR2 = log(R2);

  temp = (1.0 / (c1 + c2 * logR2 +
                 c3 * logR2 * logR2 * logR2)); // The temperature in Kelvin
  temp = temp - 273.15; // Subtracting 273.15 to get celsius

  /**
  Map the light from 0 to 100.
  */
  light =
      map(ADC_RESOLUTION - analogRead(LIGHT_SENSOR), 0.0, 1023.0, 0.0, 100.0);

  // Print the light
  Serial.println(light);

  // Print the temperature
  Serial.println(temp);
  // Loop through all the thresholds
  for (i = 0; i < (sizeof(thresholds) / sizeof(Threshold)); i++) {

    // If the perceived light is within a valid threshold
    // interval
    if (light <= thresholds[i].maxLight && light >= thresholds[i].minLight) {

      // If the perceived temperature is too hot
      if (temp > thresholds[i].maxTemp) {
        // Send high signal to red led
        digitalWrite(RED, HIGH);
        // Send low signal to green led
        digitalWrite(GREEN, LOW);
        // Send low signal to blue led
        digitalWrite(BLUE, LOW);
        break;

        // If the perceived temperature is too low
      } else if (temp < thresholds[i].minTemp) {
        // Send low signal to red led
        digitalWrite(RED, LOW);
        // Send low signal to green led
        digitalWrite(GREEN, LOW);
        // Send high signal to blue led
        digitalWrite(BLUE, HIGH);
        break;
      } else {
        // If the perceived temperature is within valid
        // interval

        // Send low signal to red led
        digitalWrite(RED, LOW);
        // Send high signal to green led
        digitalWrite(GREEN, HIGH);
        // Send low signal to blue led
        digitalWrite(BLUE, LOW);
        break;
      }
    }
  }

  delay(PERIODICITY); // Wait for 1000 millisecond(s)
}

float getmV(int pin) {
  int ADCCount; // The digital representation of analog value
  float mV;     // The millivolts

  ADCCount = analogRead(pin); // Read adc count

  // Convert the adc count to millivolt by doing
  // (ADCCount/ADCResolution) * Reference voltage
  // Example: (700 ADCc /1023 ADCr) * 5000 mV = 3417 mV
  mV = (ADCCount / ADC_RESOLUTION) * MAX_VOLT_MV;

  // Return millivolts
  return mV;
}
