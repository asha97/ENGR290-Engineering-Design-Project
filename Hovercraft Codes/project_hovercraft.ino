#include <Servo.h>
bool started = true;

//sensor
int pulse;
unsigned long pulse2;


int intput_sensor1 = 2; //pin 1 for the sensor 1, echo pin
int output_sensor1 = 3; //pin 26 PC3 for the trigger pin

int intput_sensor2 = PD4;  //pin2 for sensor 2 ultrasonic, PD4, echo pin
int output_sensor2 = PC4; //pin 27 PC4 for the trigger pin
//not sure of the pins to use for the second sensor, ask the TA

//distance sensors
int dist;
int dist2;
int xup = 50; 
int xdown= 100;
//need to change to the right values when everyhting will work well


//fan
int thrust = 10; //PB2
int lift = 7; //PD7


//servo
Servo myservo;
int servoPin = 9;
int pos = 0; 
boolean servo = 0; 

// servo angle
int angle = 127;

//fan speed
int left_speed, right_speed, init_left = 205, init_right = 220;
int _min = 0; //minimum fan speed
int _max = 255; //maximum fan speed
// change the variables names

const int RELAY_PIN = A5;  // the Arduino pin, which connects to the IN pin of relay, 
//this is for the fan


/////////////////////////////////////////////// SETUP///////////////////////////////////////
void setup()
{
 
  //interrupt for servo
  myservo.attach(9);
  pinMode(servo, OUTPUT);
  analogWrite(servo, 170);
 

 // initialize digital pin A5 as an output.
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(13, OUTPUT);
 
 //interrupt pin for the sensors
 pinMode(intput_sensor1, INPUT); //echo pin 1, PD3 
 pinMode(output_sensor1, OUTPUT); //trigger pin 1, PC3
 
 pinMode(intput_sensor2,INPUT); //echo pin 2, PD4
 pinMode(output_sensor2,OUTPUT); //trigger pin 2, PC4
 

 //interrput pin for fan
 pinMode(thrust,OUTPUT);
 analogWrite(thrust,0);

 //interrupt pins for the lift fans 
 pinMode(lift,OUTPUT);
 digitalWrite(lift,LOW);
 
  Serial.begin(9600);
}


//////////////////////////////////////////////////////VOID LOOP//////////////////////////////
void loop() 
{
   
  // put your main code here, to run repeatedly:


  //sensor_readin1();
    
    turnOnLift();
    turnOnthrust();
    sensor_readin1();
    Serial.print("Measured distance 1: ");
    Serial.println(sensor_readin1());
    if (dist <= xdown && dist >= xup)
    {
     Serial.print("Measured distance 2: ");
    Serial.println(sensor_readin2());
     servoturn();
    }

 
}


void turnOnLift()
{
  digitalWrite(lift,HIGH);
  
}

void turnOffLift()
{
  digitalWrite(lift,LOW);
  
}

void turnOnthrust()
{
      analogWrite(thrust, 255);
}

void turnOffthrust()
{
      analogWrite(thrust, 0);  // turn off fan

}

void turnright()
{
    turnOffthrust();   
    for( pos=0; pos <90; pos +=1)
    {
      myservo.write(pos);
      delay(15);
    }
  turnOnthrust();
  
}

void turnleft()
{
  
turnOffthrust();
for (pos=90; pos>=1; pos -=1)
    {
       myservo.write(pos);
      delay(15);
    }
turnOnthrust();
}


float sensor_readin1()//reading the sensors 
{

  digitalWrite(output_sensor1, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(output_sensor1, HIGH);
  delayMicroseconds(10);
  digitalWrite(output_sensor1, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int pulse = pulseIn(intput_sensor1, HIGH);
  // Calculating the distance
  return dist = pulse * 0.034 / 2;

  
}

float sensor_readin2()//reading the sensors 
{
  digitalWrite(output_sensor2, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(output_sensor2, HIGH);
  delayMicroseconds(10);
  digitalWrite(output_sensor2, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  int pulse2 = pulseIn(intput_sensor2, HIGH);
  // Calculating the distance
  return dist2 = pulse2 * 0.034 / 2;
}

void servoturn()
{
//if sensor1 sens a wall, if sensor 2 sense a wall on the left, servo turn right otherwie turn left 

  sensor_readin2();
  if (dist2 <= xdown && dist2 >= xup)
  {
    turnright();
  }
  else
  {
    turnleft();
  }
}
   
   
