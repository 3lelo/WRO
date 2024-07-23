#include <Servo.h>

Servo myservo;
const byte ir_l=22;
const byte ir_r=23;
const byte echo_f = 2;
const byte trig_f = 3;
const byte echo_r = 5;
const byte trig_r = 4;
const byte echo_l = 6;
const byte trig_l = 7;
const byte motor_f = 53;
const byte motor_b = 52;
const byte motor_s = 11;
const byte servo = 10;
int counter_rotate = 0;
const byte start_Stop = 18;
bool start_p;
float timer;
void stopProgram() {
  digitalWrite(motor_f, LOW);
  digitalWrite(motor_b, LOW);
  myservo.write(37);
  counter_rotate=0;
  start_p=0;
}
void startProgram() {
  analogWrite(motor_s, 80);
  digitalWrite(motor_f, HIGH);
  digitalWrite(motor_b, LOW);
  myservo.write(37);
  start_p=1;
}

int get_destance(int pin_Trig, int pin_Echo){
  long Time;
  int Distance;
  digitalWrite(pin_Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(pin_Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_Trig, LOW);
  Time = pulseIn(pin_Echo, HIGH);
  Time = Time / 2;
  Distance = Time * 0.034;
  return Distance;
}

void right_or_left(){
  analogWrite(motor_s, 80);
  int forward = get_destance(trig_f, echo_f);
  if (forward < 85 && forward != 0){
     delay(15);
     analogWrite(motor_s, 60);
     int right = get_destance(trig_r, echo_r);
     timer=millis();
     if (right >= 150){myservo.write(70);}
     else {myservo.write(0);}
     while(millis()-timer<=2500){
          analogWrite(motor_s, 120);
          ir();
          if(forward>120){
            break;
          }
     }
     analogWrite(motor_s, 80);
     myservo.write(37);
     delay(30);
     counter_rotate += 1;
    
   }

}


void ir(){
  analogWrite(motor_s, 80);
  
  if(digitalRead(ir_l)==0){
    myservo.write(0);
    timer=millis();
      while(millis()-timer<=1000){
         analogWrite(motor_s, 100);
         digitalWrite(motor_f, LOW);
         digitalWrite(motor_b, HIGH);
          }
          
      myservo.write(37);
     delay(300);
     digitalWrite(motor_b, LOW);
     digitalWrite(motor_f, HIGH);
     
    }
  if(digitalRead(ir_r)==0){
    myservo.write(70);
    timer=millis();
      while(millis()-timer<=1000){
         analogWrite(motor_s, 100);
         digitalWrite(motor_f, LOW);
         digitalWrite(motor_b, HIGH);
          }
      myservo.write(37);
      delay(300);
      analogWrite(motor_s, 80);
     digitalWrite(motor_b, LOW);
     digitalWrite(motor_f, HIGH);
     
    }
  }
void setup() {
  pinMode(motor_f, OUTPUT);
  pinMode(motor_b, OUTPUT);
  pinMode(motor_s, OUTPUT);
  analogWrite(motor_s, 80);
  myservo.attach(servo);
  myservo.write(37);
  pinMode(trig_f, OUTPUT);
  pinMode(echo_f, INPUT);
  pinMode(trig_l, OUTPUT);
  pinMode(echo_l, INPUT);
  pinMode(trig_r, OUTPUT);
  pinMode(echo_r, INPUT);
  pinMode(start_Stop, INPUT_PULLUP);
  Serial.begin(9600);
  
  
}


void loop() {
  if (digitalRead(start_Stop)==1){
    if(counter_rotate != 12)
    {
     startProgram();
     right_or_left();
     ir();
    }
    else if(counter_rotate == 12){
      int forward = get_destance(trig_f, echo_f);
      while (forward > 150){
        startProgram();
        right_or_left();
        ir();
      }
      stopProgram();
    }
    else{
      if (start_p=1)
          {
          stopProgram();
          } 
        }
  }
  
 else{
          stopProgram();
          } 
        }
