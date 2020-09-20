
#include "DHT.h"
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <CayenneMQTTESP8266.h>
#include <LiquidCrystal_I2C.h>
#define BLYNK_PRINT Serial
#define CAYENNE_PRINT Serial
LiquidCrystal_I2C lcd(0x27,16,2);
#define rain 16 //D0
#define light A0
#define congtacin 2 //D3
#define congtacout 0 //D4
#define A 14 //D5
#define B 12 //D6
#define DHTTYPE DHT11 
#define DHTPIN 13  // D7
DHT dht(DHTPIN, DHTTYPE);
unsigned long lastMillis = 0; 
int rainvalue,analogvalue;
int lightvalue;
int h,t;
int keo,thu,chedo;
int bien;
char auth[] = "y9idbXjnlTh4JQ_mEEPbGEKV8taNh3BK";
char ssid[] = "tranductien";
char wifiPassword[] = "0964360952";
char username[] = "ad7d9960-6683-11ea-a38a-d57172a4b4d4";
char password[] = "d69661e4f9417a1c6b1519d3919c6b02db4f0e46";
char clientID[] = "032ba690-6684-11ea-ba7c-716e7f5ba423";

BlynkTimer timer;
BLYNK_WRITE(V4)
{
  chedo = param.asInt(); 

}
BLYNK_WRITE(V5)
{
  keo = param.asInt(); 

}
BLYNK_WRITE(V6)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
{
  thu = param.asInt(); 

}
void setup()
{
Serial.begin(9600);
Blynk.begin(auth, ssid, wifiPassword);
Cayenne.begin(username, password, clientID, ssid, wifiPassword); 
dht.begin();
pinMode(light,INPUT);
pinMode(rain,INPUT);
pinMode(congtacin,INPUT_PULLUP);
pinMode(congtacout,INPUT_PULLUP);
pinMode(A,OUTPUT);
pinMode(B,OUTPUT);
lcd.init();
lcd.backlight();
lcd.setCursor(0, 0);
lcd.print(" Tran Duc Tien  ");
lcd.setCursor(0, 1);
lcd.print("MSSV:2202182013 ");
delay(2500);
lcd.setCursor(0, 0);
lcd.print("*-*- De Tai -*-*");
lcd.setCursor(0, 1);
lcd.print("Gian phoi smart ");
delay(2500);
lcd.setCursor(0, 0);
lcd.print("STATUS: IN  ");
lcd.setCursor(0, 1);
lcd.print("T:   H:   L:   %");
if(digitalRead(chedo)== 0 ){
lcd.setCursor(12, 0);
lcd.print("MANU");}
if(digitalRead(chedo)== 1 ){
lcd.setCursor(12, 0);
lcd.print("AUTO");}
timer.setInterval(1000L, sendSensor);

}


void sendSensor(){
rainvalue= digitalRead(rain);
lightvalue= map(analogRead(light),0,1023,100,0); 
h = dht.readHumidity();
t = dht.readTemperature(); 
lcd.setCursor(2, 1);
lcd.print(t);
lcd.setCursor(7, 1);
lcd.print(h);
lcd.setCursor(12, 1);
lcd.print(lightvalue/100);
lcd.setCursor(13, 1);
lcd.print(lightvalue/10);
lcd.setCursor(14, 1);
lcd.print(lightvalue%10);
if(rainvalue==1){analogvalue=2;}
if(rainvalue==0){analogvalue=85;}
Blynk.virtualWrite(V0, t);
Blynk.virtualWrite(V1, h); 
Blynk.virtualWrite(V2, lightvalue); 
Blynk.virtualWrite(V3, analogvalue); 

if (millis() - lastMillis > 10000) {
       
        lastMillis = millis(); 
        Cayenne.virtualWrite(1,t); 
        Cayenne.virtualWrite(2,h);
        Cayenne.virtualWrite(3,lightvalue); 
        Cayenne.virtualWrite(4,analogvalue);
        } 

 }
void tudong(){
  if(rainvalue ==1 && lightvalue>40){
    lcd.setCursor(8, 0);
    lcd.print("OUT");
   if( digitalRead(congtacout)==1){ chayra();}
   else if( digitalRead(congtacout)==0){ ngung();}
  }
  else if(rainvalue ==0 || lightvalue<40){
    lcd.setCursor(8, 0);
    lcd.print("IN ");
   if( digitalRead(congtacin)==1){ chayvao();}
   else if( digitalRead(congtacin)==0){ ngung();} 
  } 
  else {ngung();}
  }
void chayra(){
  digitalWrite(A,1);
  digitalWrite(B,0);
 }
void chayvao(){
  digitalWrite(A,0);
  digitalWrite(B,1);
 }  
void ngung(){
  digitalWrite(A,0);
  digitalWrite(B,0);
  }
void manual(){   

  
  if(keo==1){
    lcd.setCursor(8, 0);
    lcd.print("OUT");
   if( digitalRead(congtacout)==1){ chayra();}
   else if( digitalRead(congtacout)==0){ ngung();}
  }
  else if(thu==1){
    lcd.setCursor(8, 0);
    lcd.print("IN ");
   if( digitalRead(congtacin)==1){ chayvao();}
   else if( digitalRead(congtacin)==0){ ngung();}
    
  } 
  else {ngung();}
  }
void loop() 
{ 
  if (chedo==0){
    lcd.setCursor(12, 0);
    lcd.print("AUTO");
    tudong();}
 if (chedo==1){
   lcd.setCursor(12, 0);
   lcd.print("MANU");manual();}

//Cayenne.loop();
Blynk.run();
timer.run();
 }
