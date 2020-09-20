#include <SoftwareSerial.h>
#define led1 8
#define led2 9
#define led3 10
#define led4 11
#define led5 12
SoftwareSerial mySerial(2, 3); // RX, TX
char val;
void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  digitalWrite(led1,0);
  digitalWrite(led2,0);
  digitalWrite(led3,0);
  digitalWrite(led4,0);
  digitalWrite(led5,0);
}

void hc05(){
  if (mySerial.available()){
 val= mySerial.read(); 
  Serial.println(val);
    switch(val)
   {
  case '1' :
     digitalWrite(led1,1);
      break;
   case '2' :
     digitalWrite(led2,1);
      break;
   case '3' :
     digitalWrite(led3,1);
     break;
   case '4' :
    digitalWrite(led4,1);
     break;
   case '5' :
    digitalWrite(led5,1);
    break;
   case '9' :
   digitalWrite(led1,1);
   digitalWrite(led2,1);
   digitalWrite(led3,1);
   digitalWrite(led4,1);
   digitalWrite(led5,1);
    break;
        
  case 'A' :
     digitalWrite(led1,0);
      break;
   case 'B' :
     digitalWrite(led2,0);
      break;
   case 'C' :
     digitalWrite(led3,0);
     break;
   case 'D' :
    digitalWrite(led4,0);
     break;
   case 'E' :
    digitalWrite(led5,0);
    break;
   case 'I' :
   digitalWrite(led1,0);
   digitalWrite(led2,0);
   digitalWrite(led3,0);
   digitalWrite(led4,0);
   digitalWrite(led5,0);
     break;


    
  }
  }}

void loop() {
hc05();
}
