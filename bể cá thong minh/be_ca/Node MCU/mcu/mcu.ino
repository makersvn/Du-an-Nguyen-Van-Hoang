#include <SoftwareSerial.h> 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <string.h>
#include <Servo.h>
Servo servo; 
#define BLYNK_PRINT Serial
int timer1,timer2;
unsigned long time1 = 0;
unsigned long time2 = 0;
SoftwareSerial mcu(14,12); //RX,TX
String c="";
int A,B,C;
float D;
char auth[] = "psitEk959Pc6BFimvmr_JonyM-jCn6h2";
char ssid[] = "hoainam";
char wifiPassword[] = "123456789";

BlynkTimer timer;
WidgetLED led (V4);
 BLYNK_WRITE(V5)
{
  timer1 =param.asInt();
  Serial.print("Got a value: ");
  Serial.println(param.asStr());
}

BLYNK_WRITE(V6)
{
  timer2 = param.asInt();
  Serial.print("Got a value: ");
  Serial.println(param.asStr());
}

void setup()
{
Serial.begin(115200);  
mcu.begin(9600);
servo.attach(4); 
servo.write(90);
Blynk.begin(auth, ssid, wifiPassword);
pinMode(13,OUTPUT);
digitalWrite(13,1);
timer.setInterval(1000L, sendSensor);
}

void sendSensor(){
if( mcu.available()>0){
 c= mcu.readString();
    }
    
A=(c.toInt()/ 100000);
B=(c.toInt()/1000)%100;
C=(c.toInt()/10)%100;
D=(c.toInt()%10);
delay(1000);
Serial.print(A);
Serial.print("-");
Serial.print(B);
Serial.print("-");
Serial.print(C);
Serial.print("-");
Serial.print(D);
Serial.println();

Blynk.virtualWrite(V0, A);
Blynk.virtualWrite(V1, B); 
Blynk.virtualWrite(V2, C); 
Blynk.virtualWrite(V3, D); 
  
  }
void loop() 
{  
 Blynk.run();
timer.run();
if(digitalRead(13)==0){led.on();}
if(digitalRead(13)==1){led.off();}
if(timer1==1 || timer2==1){servo.write(40);}
else if(timer1==0 && timer2==0){servo.write(90);}
  }    
