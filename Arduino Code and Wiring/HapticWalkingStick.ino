// When an object gets close to any of the ultrasonic sensors spin the motor.

// variables
// pins
static int motorPin = 11;

static int echoPin1 = 2;
static int trigPin1 = 3;

static int echoPin2 = 4;
static int trigPin2 = 5;

static int echoPin3 = 6;
static int trigPin3 = 7;

static int echoPin4 = 8;
static int trigPin4 = 9;

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

  pinMode(motorPin, OUTPUT);  //the motor pin will output pulses of electricity
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
    analogWrite(motorPin, 255);
  }
  else {
    analogWrite(motorPin, 0);
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