#include <NewPing.h>
#include <TimerOne.h>
#define TRIGGER_PIN  5  
#define ECHO_PIN     4  
#define MAX_DISTANCE 100
#define sensor1 A0 // cảm biến 1
#define sensor2 A1 // cảm biến 2
#define sensor3 A2 // cảm biến 3
#define sensor4 A3 // cảm biến 4
#define sensor5 A4 // cảm biến 5
#define sensor6 A5 // cảm biến 5
#define sw 2 // công tắc chạm

#define LM1 11 // Động cơ trái A
#define LM2 10 // Động cơ trái B
#define RM1 9 // Động cơ phải A
#define RM2 6 // Động cơ phải B
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
int khoangcach;
void setup()
{
Serial.begin(9600);
pinMode(sensor1,INPUT);
pinMode(sensor2,INPUT);
pinMode(sensor3,INPUT);
pinMode(sensor4,INPUT);
pinMode(sensor5,INPUT);
pinMode(sw,INPUT);
pinMode(LM1, OUTPUT);
pinMode(LM2, OUTPUT);
pinMode(RM1, OUTPUT);
pinMode(RM2, OUTPUT);
delay(1000);
}
void dung(){
digitalWrite(LM1, LOW);
digitalWrite(LM2, LOW);
digitalWrite(RM1, LOW);
digitalWrite(RM2, LOW);
  
  }
void dithang(){
analogWrite(LM1, 40);
digitalWrite(LM2, LOW);
digitalWrite(RM1, LOW);
analogWrite(RM2, 45);
  }
void tranhvatcan(){
  dung();
delay(200);
analogWrite(LM1, 60);
analogWrite(LM2, 0);
analogWrite(RM1, 60);
analogWrite(RM2, 0);
delay(250);
dithang();
  delay(600);
 analogWrite(LM1, 0);
 analogWrite(LM2, 40);
 analogWrite(RM1, 0);
 analogWrite(RM2, 60);
  delay(400);
dithang();
  delay(700);
 analogWrite(LM1, 30);
 analogWrite(LM2, 0);
 analogWrite(RM1, 0);
 analogWrite(RM2, 80);
while((digitalRead(sensor4)) &&((digitalRead(sensor5)))); 
  dung();
delay(200);
analogWrite(LM1, 80);
analogWrite(LM2, 0);
analogWrite(RM1, 30);
analogWrite(RM2, 0);
delay(200);
while((digitalRead(sensor2))); 
}

void doline(){

if((digitalRead(sensor1)) && (digitalRead(sensor2))  && (digitalRead(sensor4)) && (digitalRead(sensor5)) )// Di chuyển thẳng
{
analogWrite(LM1, 40);
digitalWrite(LM2, LOW);
digitalWrite(RM1, LOW);
analogWrite(RM2, 45);
}

if(!(digitalRead(sensor2)) ) // rẽ trái 1
{

analogWrite(LM1, 0);
analogWrite(LM2, 0);
analogWrite(RM1, 0);
analogWrite(RM2, 50);

}
if(!(digitalRead(sensor1)) && !(digitalRead(sensor2))  ) // rẽ trái 2
{

analogWrite(LM1, 0);
analogWrite(LM2, 50);
analogWrite(RM1, 0);
analogWrite(RM2, 80);

}

if(!(digitalRead(sensor1))  ) // rẽ trái 3
{

analogWrite(LM1, 0);
analogWrite(LM2, 80);
analogWrite(RM1, 0);
analogWrite(RM2, 100);

}
 if(!(digitalRead(sensor4))  ) // Rẻ phải 1
{
analogWrite(LM1, 50);
analogWrite(LM2, 0);
analogWrite(RM1, 0);
analogWrite(RM2, 0);

}
 if(!(digitalRead(sensor4)) && !(digitalRead(sensor5))) // Rẻ phải 2
{
analogWrite(LM1, 80);
analogWrite(LM2, 0);
analogWrite(RM1, 50);
analogWrite(RM2, 0);}

 if(!(digitalRead(sensor5)))// Rẻ phải 3
{
analogWrite(LM1, 100);
analogWrite(LM2, 0);
analogWrite(RM1, 80);
analogWrite(RM2, 0); }

if(!(digitalRead(sensor1)) && !(digitalRead(sensor2))  && !(digitalRead(sensor4)) && !(digitalRead(sensor5)) ) // Dừng khi 5 cảm biến phát hiện vạch đen
{
digitalWrite(LM1, LOW);
digitalWrite(LM2, LOW);
digitalWrite(RM1, LOW);
digitalWrite(RM2, LOW);
}

}

void loop()
{
//  doline();
if(analogRead(sensor6)>960){
doline();  }
else tranhvatcan();

}
