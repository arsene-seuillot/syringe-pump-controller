#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <AccelStepper.h>

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();

const int stepsPerRevolution = 200; //amount for NEMA 17
const int standard_speed = 40;
const int steps_1ml = stepsPerRevolution*6/8 ;

Adafruit_StepperMotor *myMotor = AFMS.getStepper(stepsPerRevolution, 2); //200 steps, connected to M1 and M2 (define the motor)

String input1 = "not done";
String input2 = "not done";
String input3= "not done";
float currentPosition = 0;


void setup() {
  Serial.begin(9600);                     // set up Serial library at 9600 bps
  Serial.println("Test: turning mL to steps");
  AFMS.begin();   // create with the default frequency 1.6KHz    // cuestionable linea
  //AFMS.begin(1000);   // OR with a different frequency, say 1KHz
  
  myMotor->setSpeed(standard_speed);  // 40 rpm  
  Serial.println("which mL are you at ?");
  while (!Serial.available()) {
    // Attendre que l'utilisateur entre une valeur
  }
  input3 = Serial.readString(); // Lire en tant qu'entier
  input3.trim();
  float currentPosition = input3.toFloat();
  
}


void loop() {
  Serial.println("PULL or PUSH syringe?");
  
  // Wait for input1
  while (!Serial.available()) {
    // Do nothing, just wait for input
  }
  input1 = Serial.readString();
  input1.trim(); // Remove any \r \n whitespace at the end of the String
  Serial.println(input1);

  Serial.println("Please write volume in mL: ");
  
  // Wait for input2
  while (!Serial.available()) {
    // Do nothing, just wait for input
  }
  input2 = Serial.readString();
  input2.trim();
  float value = input2.toFloat();
  Serial.println(input2);
  Serial.println(value);

  int steps = value * steps_1ml; //no change!

  if(input1=="PUSH"){
    value*=-1;
  }
  
  if((currentPosition + value) >10 || (currentPosition +value <0)){
    Serial.println("Amount not allowed, try again");
  }
  else{
    
      currentPosition += value;
    
      if (input1 == "PUSH") {
        Serial.println("TURN forward double coil, amount of steps: ");
        Serial.println(steps);
        myMotor->step(steps, FORWARD, DOUBLE);
       
        delay(1000);
     }
      if (input1 == "PULL") {
        Serial.println("TURN backward Double coil, amount of steps: ");
        Serial.println(steps);
        myMotor->step(steps, BACKWARD, DOUBLE);
        
        delay(1000);
      }
  }
  
  
  delay(3000); // Add a delay before the next loop iteration
}
