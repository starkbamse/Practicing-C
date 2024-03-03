/**
 * 
 * Create a system with the proximity/distance sensor. You should use the sensor to get the
 * information about the distance to an obstacle. You should use four LEDs to indicate how close the
 * obstacle is from the sensor.
 * If the object is out of range, then no LEDs should be turn on. If the object is in range, you should turn
 * on 1, 2 or 3 LEDs, depending on the distance. If the object is too close, you should turn on four LEDs.
 * 
 * 
*/

// Definition section
#define ECHO 9 // Echo Pin
#define TRIG 8 // Trigger Pin
#define SPEED_OF_SOUND 343 // Speed of sound in m/s
#define LED1 3 // First led
#define LED2 4 // Second led 
#define LED3 5 // Third led
#define LED4 6 // Fourth led
  
int measureDistance(); // To measure distance
// To set certain LEDs on or off
void setLEDOn(int led1, int led2, int led3, int led4);

void setup()
{
  // Set echo pin to input
  pinMode(ECHO, INPUT);
  // Set trigger pin to output
  pinMode(TRIG,OUTPUT);
  // Set led 1 to output
  pinMode(LED1,OUTPUT);
  // Set led 2 to output
  pinMode(LED2,OUTPUT);
  // Set led 3 to output
  pinMode(LED3,OUTPUT);
  // Set led 4 to output
  pinMode(LED4,OUTPUT);
}
void loop(){
  // Measure the distance from the sensor
  int distance=measureDistance();  
  if(distance<250 && distance > 200){
    // If the distance is less than 250 cm
    // Turn on one led
    setLEDOn(1,0,0,0);
  }else if(distance<200 && distance > 150){
    // If the distance is less than 200 but greater than 150
    // Turn on 2 leds
    setLEDOn(1,1,0,0);
  } else if(distance<150 && distance > 100){
    // If the distance is less than 150 but greater than 100
    // Turn on 3 leds 
    setLEDOn(1,1,1,0);
  } else if (distance<100){
    // If the distance is less than 100
    // Turn on 4 leds
    setLEDOn(1,1,1,1);
  } else {
    // If outside range
    setLEDOn(0,0,0,0);
  }

   delay(1000); // Wait for 1000 millisecond(s)
  
}

void setLEDOn(int led1, int led2, int led3, int led4){
  	digitalWrite(LED1,led1); // Set led 1 status
    digitalWrite(LED2,led2); // Set led 2 status  
    digitalWrite(LED3,led3); // Set led 3 status  
    digitalWrite(LED4,led4); // Set led 4 status 
}

int measureDistance(){
  	// Set trigger pin to low
	digitalWrite(TRIG,LOW);
  	// Delay for 2 us
  	delayMicroseconds(2);
    // Transmit ultrasound
  	digitalWrite(TRIG,HIGH);
    // Delay for 10 us
  	delayMicroseconds(10);
  	// Stop transmitting ultrasound
	digitalWrite(TRIG,LOW);
  	// Read the pulse
	int time=pulseIn(ECHO,HIGH);
  	// Calculate cm per us by doing (sound speed*100)/1000000
  	float cmPerMicro=((SPEED_OF_SOUND*100.0)/1000000.0);
  	// Return half the distance to only get distance to object
  	return (time*cmPerMicro)/2;
}

