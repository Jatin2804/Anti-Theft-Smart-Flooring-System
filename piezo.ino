#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial B(10,11); //10-RX, 11-TX

const int trigPin = 8;
const int echoPin = 9;
const int buzzer = 7;
const int ledPin = 13;
const int piezoPin = A1;
const int servoPin = 12;

Servo myServo;
int safetyDistance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(piezoPin, INPUT);
  myServo.attach(servoPin);
  Serial.begin(9600);
  B.begin(9600);
}

void loop() {
  
  int piezoValue = analogRead(piezoPin);
  int distance = calculateDistance();
  Serial.println(analogRead(piezoPin));
  // Piezo sensor
  if (analogRead(piezoPin)>11) {
      digitalWrite(ledPin, HIGH);
      B.print("Thief Detected");
      B.print(";");
      delay(2000);
    }
    else {
      digitalWrite(ledPin,LOW);
      B.print("Safe");
      B.print(";");
    }

  // Ultrasonic sensor
  if (distance <= 20) { // Change the safe distance here
    digitalWrite(buzzer, HIGH);
    myServo.write(90);
  } else {
    digitalWrite(buzzer, LOW);
    myServo.write(0);
  }
}

int calculateDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  safetyDistance = distance;
  return distance;
}
