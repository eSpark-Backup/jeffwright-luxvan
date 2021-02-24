/* Arduino example sketch to control a JSN-SR04T ultrasonic distance sensor with Arduino. No library needed. More info: https://www.makerguides.com */
#include <NewPing.h>

// Define Trig and Echo pin:

#define trigPin 25
#define echoPin 26

#define MAX_DISTANCE 400

NewPing sonar = NewPing(trigPin, echoPin, MAX_DISTANCE);

// Define variables:

long duration;
int distance;

void setup() {
  // Define inputs and outputs
//  pinMode(trigPin, OUTPUT);
//  pinMode(echoPin, INPUT);
  
  // Begin Serial communication at a baudrate of 9600:
  Serial.begin(9600);

}

void loop() {
// // Clear the trigPin by setting it LOW:
//  digitalWrite(trigPin, LOW);
//  
//  
//  delayMicroseconds(5);
// // Trigger the sensor by setting the trigPin high for 10 microseconds:
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  
//  // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds:
//  duration = pulseIn(echoPin, HIGH);
//  
//  // Calculate the distance:
//  distance = (duration*0.034/2)/2.54;
//  
//  // Print the distance on the Serial Monitor (Ctrl+Shift+M):
//  Serial.print("Distance = ");
//  Serial.print(distance);
//  Serial.println(" in");
//  
//  delay(100);

    delay(50);
    // Measure distance and print to the Serial Monitor:
    Serial.print("Distance = ");
    // Send ping, get distance in cm and print result (0 = outside set distance range):
    float distance = sonar.ping_cm();
    distance = distance / 2.54;
    Serial.print(distance); 
    Serial.println(" inch");
}
