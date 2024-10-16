#include <Stepper.h>

// Defines the number of steps per rotation
const int stepsPerRevolution = 2038/64;
const int rotSpeed = 30;

//pin define
int trigPin = 2;
int echoPin = 3;
int motion = 12;
int relay = 13;
int i = 0;

// Creates an instance of stepper class
// Pins entered in sequence IN1-IN3-IN2-IN4 for proper step sequence
Stepper LRstepper = Stepper(stepsPerRevolution, 8, 10, 9, 11); // y,b,g,p
Stepper UDstepper = Stepper(stepsPerRevolution, 4, 6, 5, 7); // y,b,g,p

//motion sensor variable
bool detected = false;

//main tracking code
void track(){
  //default range
  int limit = 50;
  //Serial.println("tracking");
  bool timeUp = false;
  while (timeUp == false){
    if (Serial.available()>0 && timeUp == false) {
      
      bool getLim = false;
      int in = Serial.read();
      if (in == 48){
        LRstepper.setSpeed(rotSpeed);
        LRstepper.step(-stepsPerRevolution);
      }else if (in == 49){
        LRstepper.setSpeed(rotSpeed);
        LRstepper.step(stepsPerRevolution);
      }else if (in == 50){
        UDstepper.setSpeed(rotSpeed);
        UDstepper.step(stepsPerRevolution);
      }else if (in == 51){
        UDstepper.setSpeed(rotSpeed);
        UDstepper.step(-stepsPerRevolution);
      }else if (in == 52){
        if (Serial.available()>0 && getLim == false){
          String in = Serial.readStringUntil('\n');
          limit = in.toInt();
          getLim = true;
          //Serial.println(limit);
        }
        digitalWrite(trigPin, LOW);
        delayMicroseconds(2);
        digitalWrite(trigPin, HIGH);
        delayMicroseconds(10);
        digitalWrite(trigPin, LOW);
        int duration = pulseIn(echoPin, HIGH);
        int distance = duration * 0.034 / 2;
        
        if(distance < limit){
          digitalWrite(relay, HIGH);
          //Serial.println("Distance: " + String(distance));
          delay(1000);
        }
      }else if(in == 53){
          //Serial.println("warning");
          digitalWrite(A1, HIGH);
      }else if (in = 54){
        timeUp = true;
        digitalWrite(A0, LOW);
      }
      digitalWrite(relay, LOW);
    }else if(timeUp == true){
      break;
    }
  }
}

//setup
void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(motion, INPUT);
  pinMode(relay, OUTPUT);
}

//main loop
void loop(){
  if (digitalRead(motion) == HIGH && detected == false) {   
    detected = true;// check if the sensor is HIGH
    digitalWrite(A0, HIGH);   // motion check light
    delay(100);                // delay 100 milliseconds
    Serial.println("1");
    delay(500);
    //Serial.println("track");
    track();
    //Serial.println("ending tracking");
  } 
  else if (digitalRead(motion) == LOW && detected == true){
    detected = false;
    digitalWrite(A0, LOW); // turn LED OFF
    delay(200);             // delay 200 milliseconds 
    
  }
}

  
