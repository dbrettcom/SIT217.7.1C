#include "SoftwareSerial.h"
SoftwareSerial mySerial(0, 1); // RX | TX

char t;
int buzzer = 2;
int trigPin = A0;   
int echoPin = A1;    

long duration, distance;

// Motor A

int enA = 8;
int in1 = 7;
int in2 = 6;

// Motor B

int enB = 3;
int in3 = 5;
int in4 = 4;

void setup() 
{
  Serial.begin(9600);
  Serial.println("Bluetooth Connected");

  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT); 
  pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); 
  pinMode(in4, OUTPUT);
  pinMode(buzzer, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}



void loop() 
{
  if (Serial.available())
  {
    t = Serial.read();
    Serial.println(t);
  }

  if(t == 'X')
  {
      Serial.println("Autonomous Mode");
      digitalWrite(trigPin, LOW);
      delayMicroseconds(2);   
      digitalWrite(trigPin, HIGH);    
      delayMicroseconds(10);
      duration = pulseIn(echoPin, HIGH); 
      distance = duration / 58.2;  
      delay(10); 
      Serial.print(distance);
      delay(100); 

     while (distance > 20)
     {
        Serial.println("Forward at Low Speed");
        analogWrite(enA, 150);
        analogWrite(enB, 150);
  
        digitalWrite(in1,HIGH);
        digitalWrite(in2,LOW);
        digitalWrite(in3,LOW);
        digitalWrite(in4,HIGH); 
        
        delay(100);   
     }
  }

  if (t == 'F') 
  {
    Serial.println("Forward");
    analogWrite(enA, 200);
    analogWrite(enB, 200);
  
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    digitalWrite(in3,LOW);
    digitalWrite(in4,HIGH); 
  }     

   else if (t == 'B')
   {
      Serial.println("Reverse");
      analogWrite(enA, 200);
      analogWrite(enB, 200);

      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
   }

   else if (t == 'R')
   {
      Serial.println("Right");
      analogWrite(enA, 200);
      analogWrite(enB, 200);

      digitalWrite(in1,HIGH);
      digitalWrite(in2,LOW);
      digitalWrite(in3,HIGH);
      digitalWrite(in4,LOW);
   }
   
   else if (t == 'L')
   {
      Serial.println("Left");
      analogWrite(enA, 200);
      analogWrite(enB, 200);

      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
   }

   else if (t == 'V') //Buzzer On
   {
    tone(buzzer, 1000);
    delay(1000);
    noTone(buzzer);
    delay(1000);
   }

   else if (t == 'v') //Buzzer Off
   {
    tone(buzzer, 0);
    delay(1000);
    noTone(buzzer);
    delay(1000);
   }
  
   else
   {
      Serial.println("Stop");
      analogWrite(enA, 0);
      analogWrite(enB, 0);
      digitalWrite(in1,HIGH);
      digitalWrite(in2,HIGH);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);
   }
}
