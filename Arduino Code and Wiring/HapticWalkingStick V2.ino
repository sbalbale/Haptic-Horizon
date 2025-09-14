// When an object gets close to any of the ultrasonic sensors spin the motor.

// variables
// pins
//static int motorPin = 11;

static int echoPin1 = 2;
static int trigPin1 = 3;

static int echoPin2 = 4;
static int trigPin2 = 5;

static int echoPin3 = 6;
static int trigPin3 = 7;

static int echoPin4 = 8;
static int trigPin4 = 9;

const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor
const int PWMA = 11;            //speed control pin on the motor driver for the right motor

// distances
long distance1;
long distance2;
long distance3;
long distance4;

static int alarmDistance = 20;




void setup()
{
  Serial.begin (9600);        //set up a serial connection with the computer

  pinMode(trigPin1, OUTPUT);   //the trigger pin will output pulses of electricity
  pinMode(echoPin1, INPUT);    //the echo pin will measure the duration of pulses coming back from the distance sensor

  pinMode(trigPin2, OUTPUT);   //the trigger pin will output pulses of electricity
  pinMode(echoPin2, INPUT);    //the echo pin will measure the duration of pulses coming back from the distance sensor

  pinMode(trigPin3, OUTPUT);   //the trigger pin will output pulses of electricity
  pinMode(echoPin3, INPUT);    //the echo pin will measure the duration of pulses coming back from the distance sensor

  pinMode(trigPin4, OUTPUT);   //the trigger pin will output pulses of electricity
  pinMode(echoPin4, INPUT);    //the echo pin will measure the duration of pulses coming back from the distance sensor

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
}

void loop()
{
  distance1 = getDistance(trigPin1, echoPin1);   //variable to store the distance measured by the sensor
  Serial.print("Sensor 1: ");
  Serial.print(distance1);     //print the distance that was measured
  Serial.println(" in");      //print units after the distance

  distance2 = getDistance(trigPin2, echoPin2);   //variable to store the distance measured by the sensor
  Serial.print("Sensor 2: ");
  Serial.print(distance2);     //print the distance that was measured
  Serial.println(" in");      //print units after the distance

  distance3 = getDistance(trigPin3, echoPin3);   //variable to store the distance measured by the sensor
  Serial.print("Sensor 3: ");
  Serial.print(distance3);     //print the distance that was measured
  Serial.println(" in");      //print units after the distance

  distance4 = getDistance(trigPin4, echoPin4);   //variable to store the distance measured by the sensor
  Serial.print("Sensor 4: ");
  Serial.print(distance4);     //print the distance that was measured
  Serial.println(" in");      //print units after the distance

  if (distance1 <= alarmDistance || distance2 <= alarmDistance || distance3 <= alarmDistance || distance4 <= alarmDistance) {                       //if the object is close
    spinMotor(255);
  }
  else {
    spinMotor(0);
  }
}


//------------------FUNCTIONS-------------------------------

//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance(int funcTrigPin, int funcEchoPin)
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(funcTrigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(funcTrigPin, LOW);

  echoTime = pulseIn(funcEchoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
}

void spinMotor(int motorSpeed)                       //function for driving the right motor
{
  if (motorSpeed > 0)                                 //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);                         //set pin 1 to high
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  else if (motorSpeed < 0)                            //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, HIGH);                         //set pin 2 to high
  }
  else                                                //if the motor should stop
  {
    digitalWrite(AIN1, LOW);                          //set pin 1 to low
    digitalWrite(AIN2, LOW);                          //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
}