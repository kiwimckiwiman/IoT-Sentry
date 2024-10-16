#define LRpot A0
#define UDpot A1
#define LRSTEPPER_PIN_1 5 //yellow
#define LRSTEPPER_PIN_2 4
#define LRSTEPPER_PIN_3 3
#define LRSTEPPER_PIN_4 2 //purple

#define UDSTEPPER_PIN_1 11 //yellow
#define UDSTEPPER_PIN_2 10
#define UDSTEPPER_PIN_3 9
#define UDSTEPPER_PIN_4 8 //purple
int lrstep_number = 0;
int udstep_number = 0;
void setup() {
  // initialize serial communication at 9600 bits per second:
  pinMode(LRSTEPPER_PIN_1, OUTPUT);
  pinMode(LRSTEPPER_PIN_2, OUTPUT);
  pinMode(LRSTEPPER_PIN_3, OUTPUT);
  pinMode(LRSTEPPER_PIN_4, OUTPUT);
  pinMode(UDSTEPPER_PIN_1, OUTPUT);
  pinMode(UDSTEPPER_PIN_2, OUTPUT);
  pinMode(UDSTEPPER_PIN_3, OUTPUT);
  pinMode(UDSTEPPER_PIN_4, OUTPUT);
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  // print out the value you read:
  int lr = analogRead(LRpot);
  int ud = analogRead(UDpot);
  Serial.print("LR = ");
  Serial.print(lr);
  Serial.print("| UD = ");
  Serial.println(ud);
  delay(1);  // delay in between reads for stability

  if(lr < 512){
    LRStep(true);
    delay(50);
  }else{
    LRStep(false);
    delay(50);
  }

  if(ud < 512){
    UDStep(true);
    delay(50);
  }else{
    UDStep(false);
    delay(50);
  }
}

void LRStep(bool dir){
    if(dir){
      switch(lrstep_number){
        case 0:
        digitalWrite(LRSTEPPER_PIN_1, HIGH);
        digitalWrite(LRSTEPPER_PIN_2, LOW);
        digitalWrite(LRSTEPPER_PIN_3, LOW);
        digitalWrite(LRSTEPPER_PIN_4, LOW);
        break;
        case 1:
        digitalWrite(LRSTEPPER_PIN_1, LOW);
        digitalWrite(LRSTEPPER_PIN_2, HIGH);
        digitalWrite(LRSTEPPER_PIN_3, LOW);
        digitalWrite(LRSTEPPER_PIN_4, LOW);
        break;
        case 2:
        digitalWrite(LRSTEPPER_PIN_1, LOW);
        digitalWrite(LRSTEPPER_PIN_2, LOW);
        digitalWrite(LRSTEPPER_PIN_3, HIGH);
        digitalWrite(LRSTEPPER_PIN_4, LOW);
        break;
        case 3:
        digitalWrite(LRSTEPPER_PIN_1, LOW);
        digitalWrite(LRSTEPPER_PIN_2, LOW);
        digitalWrite(LRSTEPPER_PIN_3, LOW);
        digitalWrite(LRSTEPPER_PIN_4, HIGH);
        break;
      } 
    }else{
      switch(lrstep_number){
        case 0:
        digitalWrite(LRSTEPPER_PIN_1, LOW);
        digitalWrite(LRSTEPPER_PIN_2, LOW);
        digitalWrite(LRSTEPPER_PIN_3, LOW);
        digitalWrite(LRSTEPPER_PIN_4, HIGH);
        break;
        case 1:
        digitalWrite(LRSTEPPER_PIN_1, LOW);
        digitalWrite(LRSTEPPER_PIN_2, LOW);
        digitalWrite(LRSTEPPER_PIN_3, HIGH);
        digitalWrite(LRSTEPPER_PIN_4, LOW);
        break;
        case 2:
        digitalWrite(LRSTEPPER_PIN_1, LOW);
        digitalWrite(LRSTEPPER_PIN_2, HIGH);
        digitalWrite(LRSTEPPER_PIN_3, LOW);
        digitalWrite(LRSTEPPER_PIN_4, LOW);
        break;
        case 3:
        digitalWrite(LRSTEPPER_PIN_1, HIGH);
        digitalWrite(LRSTEPPER_PIN_2, LOW);
        digitalWrite(LRSTEPPER_PIN_3, LOW);
        digitalWrite(LRSTEPPER_PIN_4, LOW);
      } 
    }
  lrstep_number++;
  if(lrstep_number > 3){
    lrstep_number = 0;
  }
}

void UDStep(bool dir){
    if(dir){
      switch(udstep_number){
        case 0:
        digitalWrite(UDSTEPPER_PIN_1, HIGH);
        digitalWrite(UDSTEPPER_PIN_2, LOW);
        digitalWrite(UDSTEPPER_PIN_3, LOW);
        digitalWrite(UDSTEPPER_PIN_4, LOW);
        break;
        case 1:
        digitalWrite(UDSTEPPER_PIN_1, LOW);
        digitalWrite(UDSTEPPER_PIN_2, HIGH);
        digitalWrite(UDSTEPPER_PIN_3, LOW);
        digitalWrite(UDSTEPPER_PIN_4, LOW);
        break;
        case 2:
        digitalWrite(UDSTEPPER_PIN_1, LOW);
        digitalWrite(UDSTEPPER_PIN_2, LOW);
        digitalWrite(UDSTEPPER_PIN_3, HIGH);
        digitalWrite(UDSTEPPER_PIN_4, LOW);
        break;
        case 3:
        digitalWrite(UDSTEPPER_PIN_1, LOW);
        digitalWrite(UDSTEPPER_PIN_2, LOW);
        digitalWrite(UDSTEPPER_PIN_3, LOW);
        digitalWrite(UDSTEPPER_PIN_4, HIGH);
        break;
      } 
    }else{
      switch(udstep_number){
        case 0:
        digitalWrite(UDSTEPPER_PIN_1, LOW);
        digitalWrite(UDSTEPPER_PIN_2, LOW);
        digitalWrite(UDSTEPPER_PIN_3, LOW);
        digitalWrite(UDSTEPPER_PIN_4, HIGH);
        break;
        case 1:
        digitalWrite(UDSTEPPER_PIN_1, LOW);
        digitalWrite(UDSTEPPER_PIN_2, LOW);
        digitalWrite(UDSTEPPER_PIN_3, HIGH);
        digitalWrite(UDSTEPPER_PIN_4, LOW);
        break;
        case 2:
        digitalWrite(UDSTEPPER_PIN_1, LOW);
        digitalWrite(UDSTEPPER_PIN_2, HIGH);
        digitalWrite(UDSTEPPER_PIN_3, LOW);
        digitalWrite(UDSTEPPER_PIN_4, LOW);
        break;
        case 3:
        digitalWrite(UDSTEPPER_PIN_1, HIGH);
        digitalWrite(UDSTEPPER_PIN_2, LOW);
        digitalWrite(UDSTEPPER_PIN_3, LOW);
        digitalWrite(UDSTEPPER_PIN_4, LOW);
      } 
    }
  udstep_number++;
  if(udstep_number > 3){
    udstep_number = 0;
  }
}