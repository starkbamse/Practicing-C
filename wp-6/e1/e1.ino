// (C) __Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 __ (2024)
// Work package 6
// Exercise 1
// Submission code: xxxxxx

#define ENCA 2 // Encoder channel A
#define ENCB 3 // Encoder channel B
#define PWM1 5 // Input 1
#define PWM2 6 // Input 2

// --- Function declarations ---
// Get desired position input in degrees from the user
int getInput();
// Calculate u_out which is used as speed
int getAction(int error);
// ISR which increments or decrements position based on cw or ccw rotation
void ISR_readEncoder();
// --- Function declarations ---

// --- Variable declarations ---
volatile int pos = 0; // Position in ticks
int deg = 0; // Position in degrees
int degtarget = 0; // Target position in degrees
int speed = 0; // Desired motor speed
int kp = 5; // Proportional constant for controller (tuning parameter)
int u_out = 0; // output of controller
int e = 0; // error
int a = 0; // a-encoder signal
int b = 0; // b-encoder signal
// --- Variable declarations ---

/**
 * This program controls a DC motor with encoder using Arduino uno, a 12v power supply and a motor driver.
 * The user inputs a desired position in degrees, using the serial monitor. THe program uses the encoders'
 * Signal A and B and calculates the position of the motor. the postion is a number between 0 and 2299 which
 * corresponds to 0 and 360 in degrees. The program then calculates the speed (and hence direction) based on the
 * current position and the desired postion of the motor.
*/

void setup() {
 
  Serial.begin(9600);
  pinMode(ENCA,INPUT_PULLUP);
  pinMode(ENCB,INPUT_PULLUP);
  pinMode(PWM1,OUTPUT);
  pinMode(PWM2,OUTPUT);  
  
  /*
  ==> TO DO TO DO TO DO
  ATTACH INTERRUPT HERE.
  */
  attachInterrupt(digitalPinToInterrupt(ENCA), ISR_readEncoder, RISING);
  
  // Start the motor, just a tiny little bit because otherwise TinkerCad dies....
  analogWrite(PWM2, 10); 
  delay(1000); // TinkerCad bug
  analogWrite(PWM1, 10);
}

void loop() {
  // Stop the motor, but not to zero because then TinkerCad dies....
  analogWrite(PWM1, 10);
  delay(1000); // TinkerCad...bug
  analogWrite(PWM2, 10);
  
  // Check if motor rotated all the way around, and reset counter
  if (pos > 2299){
    deg = deg - 359;
    pos = pos - 2299;
  }
  if (pos < 0){
    deg = 359 + deg;
    pos = 2299 + pos;
  }
  
  // Print current position
  Serial.print("The current position is: ");
  Serial.print(deg);
  Serial.print("\n");
   
  // Get input 
  degtarget = getInput();
  
  // Calculate initial error
  e = degtarget - deg;
    
  // Loop until error is zero
  while(e){
    
    // Map current position into degrees
    deg = map(pos,0,2299,0,359);
       
  	// Get necessary speed signal
  	speed = getAction(e);
    
  	// Send speed signal to motor
    // Rotating clockwise
    if(speed >= 0){
    	if (speed < 100) // motor does not react with too low inputs
      	speed = 100;
      analogWrite(PWM2, 0);
      analogWrite(PWM1, speed);
  	}
  
    // Rotating counter-clockwise
  	else{
    	if (-speed < 100) // motor does not react with too low inputs
      	speed = -100; 
      analogWrite(PWM1, 0);
      analogWrite(PWM2, -speed); 
    }

    // Calculate new error
  	e = degtarget - deg;
  }
}

int getInput(){
  int ready = 0; // This variable wil hold the value returned by Serial.readBytes()
  char buf[3]; // We ony accept 1 to 3 digit numbers
  int input = -1; // Initial input is -1
  
  // Ask the user to input the position they want
  Serial.print("Please enter the desired position: \n");
  
  // While there input to read, meaning tht Serial.readBytes() does not return 0,
  // read input
  while(!ready){
    ready = Serial.readBytes(buf,3);
    // Convert to integer. Note that if provided input is not an integer, 0 will be returned.
    input = atoi(&buf[0]);
  }
    
  // Return input
  return input;
}  

int getAction(int error){
  /*
  ==> TO DO TO DO TO DO
  Calculate u_out as function of the error and the kp (tuning parameter).
  */
  // u_out is kp constant times the error
  u_out = kp * error;
  
  //u_out cannot be more than 255...
  if (u_out > 254){ 
  	return 255;
  }
  //...or less than -254
  else if (u_out < -254){ 
    return -255;
  }  
  else
     return u_out;
}

void ISR_readEncoder(){
  /*
  ==> TO DO TO DO TO DO
  READ THE ENCODER SIGNAL HERE.
  Read the encoder signals and increase or decrease pos accordingly.
  */
  // The interrupt service routing happens when signal A rises. At that point, if signal B
  // is low, then we are moving clock-wise, and if signal B is high, then we are moving anti clock-wise

  // Read the value of channel B
  b = digitalRead(ENCB);
  // If it is low, then we are moving clockwise, otherwise, we are moving anti clockwise
  if (b == LOW) {
    pos++;
  } else {
    pos--;
  }

  // Check if motor rotated all the way around, and reset pos counter
  if (pos > 2299){
    pos = pos - 2299;
  }
  if (pos < 0){
    pos = 2299 + pos;
  }

}