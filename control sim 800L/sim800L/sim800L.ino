#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);
#include <SoftwareSerial.h>
SoftwareSerial mySerial(3, 2);
 
char incomingByte; 
String incomingData;
bool atCommand = true;
 
#define OUT1 4
#define OUT2 5
#define button1 6
#define button2 7
int index = 0;
int bien=0;
int bien1=0;
int val;
String number = "";
String message = "";
 
void setup(){
    Serial.begin(9600);
    mySerial.begin(9600);
  pinMode(OUT1, OUTPUT);
  pinMode(OUT2, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  digitalWrite(OUT1,LOW);
  digitalWrite(OUT2,LOW);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Dieu khien thiet");
  lcd.setCursor(0,1);
  lcd.print("bi bang Sim 800L");
  delay(4000);
  lcd.setCursor(0,0);
  lcd.print("Nguyen Van Thanh");
  lcd.setCursor(0,1);
  lcd.print("MSSV: 2202180040");
   while(!mySerial.available()){
      mySerial.println("AT");
      delay(1000); 
      Serial.println("connecting....");
    }
    Serial.println("Connected..");  
    mySerial.println("AT+CMGF=1");  //Set SMS Text Mode 
    delay(1000);  
    mySerial.println("AT+CNMI=1,2,0,0,0");  //procedure, how to receive messages from the network
    delay(1000);
    mySerial.println("AT+CMGL=\"REC UNREAD\""); // Read unread messages
    Serial.println("Ready to receive Commands..");  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" OUTPUT1 :  off  ");
  lcd.setCursor(0,1);
  lcd.print(" OUTPUT2 :  off  "); 
 }
 
void manual(){
if(digitalRead(button1)==0){
    bien++; while(digitalRead(button1)==0);
  if (bien==2){bien=0;}
    }
if(digitalRead(button2)==0){
    bien1++; while(digitalRead(button2)==0);
  if (bien1==2){bien1=0;}
    }  
if (bien==1 || val==1){ 
      digitalWrite(OUT1, HIGH);
      lcd.setCursor(12,0); 
      lcd.print("on ");}    
  
if (bien==0 && val==2){ 
      digitalWrite(OUT1, LOW);
      lcd.setCursor(12,0); 
      lcd.print("off");}
if (bien1==1 || val==3){ 
      digitalWrite(OUT2, HIGH);
      lcd.setCursor(12,1); 
      lcd.print("on ");}     
if(bien1==0&& val==4){ 
      digitalWrite(OUT2, LOW);
      lcd.setCursor(12,1); 
      lcd.print("off");} 
}
 
void loop(){  
  if(mySerial.available()){
      delay(100);
      // Serial buffer
      while(mySerial.available()){
        incomingByte = mySerial.read();
        incomingData += incomingByte;
       }
        delay(10); 
        if(atCommand == false){
          receivedMessage(incomingData);
        }
        else{
          atCommand = false;
        }        
        //delete messages to save memory
        if (incomingData.indexOf("OK") == -1){
          mySerial.println("AT+CMGDA=\"DEL ALL\"");
          delay(1000);
          atCommand = true;
        }        
        incomingData = "";
  }

 manual(); 
}
 
void receivedMessage(String inputString){
   
  //Get The number of the sender
  index = inputString.indexOf('"')+1;
  inputString = inputString.substring(index);
  index = inputString.indexOf('"');
  number = inputString.substring(0,index);
  Serial.println("Number: " + number);
 
  //Get The Message of the sender
  index = inputString.indexOf("\n")+1;
  message = inputString.substring(index);
  message.trim();
  Serial.println("Message: " + message);
        
  message.toUpperCase(); // uppercase the message received
 
  //điều khiển thiết bị
  if (message.indexOf("ON1") > -1){
      val=1;
      Serial.println("Command: Lamp1 Turn On.");
   }          
  if (message.indexOf("OFF1") > -1){
      val=2;
      Serial.println("Command: Lamp1 Turn Off.");
   }  

  if (message.indexOf("ON2") > -1){
      val=3;
      Serial.println("Command: Lamp2 Turn On.");
   }          
  if (message.indexOf("OFF2") > -1){
      val=4;
      Serial.println("Command: Lamp2 Turn Off.");
   }  
        
   delay(50);
  }
