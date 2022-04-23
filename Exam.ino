//Autonomous Vehicle
//Author: Sanya Sharma
//Date: January 22, 2020
//Description: The code below drives a car forward and when an obstacle is encountered it choose to turn left or right. While backing up before turning it makes beeping sounds.



const int rightFor = 12; //When the right wheel is turning clockwise it is on pin 12
const int rightBack = 11;//When the right wheel is turning anticlockwise it is on pin 11
const int leftFor = 6;//When the left wheel is turning clockwise it is on pin 6
const int leftBack = 5;//When the left wheel is turning anticlockwise it is on pin 5
const int trigPin = 8; // Trig pin on the Ultrasonic Sensor is on pin 9
const int echoPin = 10;// echo pin on the Ultrasonic Sensor is on pin 10
const int headA = 4;// ledA is on pin 4
const int headB = 7;// ledB is on pin 7
const int piezo = 9; // buzzer at pin 9
int nextNo = 2500;
int restart = 3000;
int beep = 2000;
long duration; //variable for the ultrasonic readings
int distance;//variable for the ultrasonic readings
long randNumber;//variable for the random number function

void setup()
{
  pinMode(rightFor, OUTPUT);//rightForward wheel is set as output
  pinMode(rightBack, OUTPUT);//rightBack wheel is set as output
  pinMode(leftFor, OUTPUT);// leftFor wheel is set as output
  pinMode(leftBack, OUTPUT);// wheel is set as output
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(headA, OUTPUT);// ledA is set as output
  pinMode(headB, OUTPUT);// ledB is set as output
  pinMode(piezo, OUTPUT); // setting speaker as Output
  pinMode(headA, HIGH);// default status of led on
  pinMode(headB, HIGH);// default status of led on

  Serial.begin(9600); // Starts the serial communication
}

void stop() //Function to bring the speed of the motor 0
{
  analogWrite(rightFor, 0);
  analogWrite(rightBack, 0);
  analogWrite(leftFor, 0);
  analogWrite(leftBack, 0);
  delay(1500);
}

void goBackwards()// Function to move backwards
{
  digitalWrite(rightFor, LOW);
  digitalWrite(rightBack, HIGH);
  digitalWrite(leftFor, LOW);
  digitalWrite(leftBack, HIGH);
  digitalWrite(headA, LOW);
  digitalWrite(headB, LOW);
  tone(piezo, beep, 1000); // Code for the dash
  delay(1500);
  tone(piezo, beep, 1000); // Code for the dash
  delay(1500);
  tone(piezo, beep, 1000); // Code for the dash
  delay(1500);
}

void goForward()// Function to go forward
{
  digitalWrite(rightFor, HIGH);
  digitalWrite(rightBack, LOW);
  digitalWrite(leftFor, HIGH);
  digitalWrite(leftBack, LOW);
  digitalWrite(headA, HIGH);
  digitalWrite(headB, HIGH);
  delay(1000);
}

void turnRight()// Function to turn right
{
  digitalWrite(rightFor, LOW);
  digitalWrite(rightBack, HIGH);
  analogWrite(rightBack, 90);
  digitalWrite(leftFor, HIGH);
  digitalWrite(leftBack, LOW);
  analogWrite(leftBack, 90);
  digitalWrite(headA, LOW);
  digitalWrite(headB, LOW);
  delay(1000);
}

void turnLeft()// Function to turn left
{
  digitalWrite(rightFor, HIGH);
  analogWrite(rightFor, 90);
  digitalWrite(rightBack, LOW);
  digitalWrite(leftFor, LOW);
  digitalWrite(leftBack, HIGH);
  analogWrite(leftBack, 90);
  digitalWrite(headA, LOW);
  digitalWrite(headB, LOW);
  delay(1000);
}

void loop()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2;
  // Prints the distance on the Serial Monitor
  Serial.print("   Distance: ");
  Serial.println(distance);
  randNumber = random(2);// Generate a random number from 0 to 2
  Serial.print("Random Number: ");// Print the number on the serial monitor
  Serial.println(randNumber);



  if (randNumber == 0 && distance <= 30)//if random number is 0 and distance between the object and the car is less than 20 following the following functions
  {
    stop;
    goBackwards();
    turnLeft();
    goForward();
    Serial.print("Left"); // Print the direction on the Serial Monitor
  }

  else if (randNumber == 1 && distance <= 30)// if random number is 1 and the distance between the object and the car is less than 20 following the following functions
  {
    stop;
    goBackwards();
    delay(1000);
    turnRight();
    goForward();
    Serial.print("Right"); // Print the direction on the Serial Monitor
  }
 
  else// if any of the above conditions not met just drive forward
  {
    goForward();
  }
}
