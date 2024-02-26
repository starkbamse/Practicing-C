// (C) Omid Khodaparast, Alexander Säfström, Kaisa Arumeel, group: 2 (2024)
// Work package 6
// Exercise 1
// Submission code: 

// declare pins for encoder
#define ENC1 2
#define ENC2 3
// declare pins for motor driver
#define MOTOR_POWER_1 5
#define MOTOR_POWER_2 6
 
volatile int position = 0; // Position in ticks
int currentDegree = 0; // Position in degrees
int targetDegree = 0; // Target position in degrees
int toRotate = 0; // The amount of degrees left to rotate
int speed = 0; // Desired motor speed

int kp = 5; // Proportional constant for controller (tuning parameter)
int u_out = 0; // output of controller
int a = 25; // a-encoder signal
int b = 0; // b-encoder signal

void setup() {
 
  Serial.begin(9600); // Begin the serial
  pinMode(ENC1,INPUT_PULLUP); // Set the encoder pins to input
  pinMode(ENC2,INPUT_PULLUP); // Set the encoder pins to input
  pinMode(MOTOR_POWER_1,OUTPUT); // Set the DC motor power pins to output
  pinMode(MOTOR_POWER_2,OUTPUT); // Set the DC motor power pins to output 
  
  // Attach interrupt to encoder 1 when rising
  attachInterrupt(digitalPinToInterrupt(ENC1), ISR_readEncoder, RISING);

  // Start the motor
  analogWrite(MOTOR_POWER_1, 10); 
  analogWrite(MOTOR_POWER_2, 10);
}

void loop() {
  // Stop the motor, but not to zero because then TinkerCad dies....
  analogWrite(MOTOR_POWER_1, 10);
  analogWrite(MOTOR_POWER_2, 10);
  
  // Check if motor rotated all the way around
    if (position > 2299){
      // Reset the position counter.
      position = position - 2299;
      // Start a new round of degrees
      currentDegree = currentDegree - 359;
    }
  	// Check if the motor is rotated all the way back
    if (position < 0){
      // Reset the position counter.
  	  position = 2299 + position;
      // Then start a new round of degrees
      currentDegree = 359 + currentDegree;
    }

  // Get the user input 
  targetDegree = getInput();
  // Calculate the amount to rotate to achieve the target degree.
  toRotate = targetDegree - currentDegree;
    
  // Loop until there are degrees to rotate
  while(toRotate){
    // Map current position into degrees
    currentDegree = map(position,0,2299,0,359);
    
    // Print the current position to the user.
    Serial.print("Current position is ");
    Serial.print(currentDegree);
    Serial.print(" degrees.");
    Serial.println();
    
  	// Get necessary speed signal
  	speed = getAction(toRotate);
    
  	// Send speed signal to motor
    // Rotating clockwise
    if(speed >= 0 && speed < 100 ){
    	if (speed < 100) // motor does not react with too low inputs
      	speed = 100;
      analogWrite(MOTOR_POWER_2, 0);
      analogWrite(MOTOR_POWER_1, speed);
  	}
  
    // Rotating counter-clockwise
  	else{
    	if (-speed < 100) // motor does not react with too low inputs
      	speed = -100; 
      analogWrite(MOTOR_POWER_1, 0);
      analogWrite(MOTOR_POWER_2, -speed); 
    }
	
    // Calculate new amount of degrees to rotate
  	toRotate = targetDegree - currentDegree;
  }
}

int getInput(){
  
  int ready = 0;
  char buf[3];
  int input = -1;
  
  Serial.print("Please enter the desired position: \n");
  
  while(!ready){
    ready = Serial.readBytes(buf,3);
    input = atoi(&buf[0]);
  }
  Serial.print("input is ");
  Serial.println(input);
  return input;
}  

int getAction(int error){

  // here we used the formula recommended in the exercise description
  u_out = kp * error;
  
  if (u_out > 254){ //u_out cannot be more than 255...
  	return 255;
  }
  else if (u_out < -254){ //...or less than -254
    return -255;
  }  
  else
     return u_out;
}
// this function is called when encoder A is set to high
void ISR_readEncoder(){

  // read encoder B
  int b = digitalRead(ENC2);
  // if b is set to low, then its going counterclockwise
  if (b == 0){
    // increase the tick counter
    a++;
  // if b is also set to high, then its going clockwise
  } else {
    // decrease tick counter
  	a--;
  }
  // set tick counter to positive equivalent (6500 is the NR of ticks per revolution)
  // this is done so we can map the position to the a value
  if (a < 0){
  	a= 6149 + a;
  } 
  // map position to a value
  position = map(a, 0, 6149, 0, 2299); 
}