#define BLYNK_PRINT Serial                        
#include <ESP8266WiFi.h>                         
#include <BlynkSimpleEsp8266.h>                 
#include <DHT.h>                               
#include <Wire.h>                             
#include <DS1307.h>                          
#include <LiquidCrystal_I2C.h>              
#include <Servo.h>                       
LiquidCrystal_I2C lcd(0x27,16,2);
Servo servo;
#define quat 0      //D3                   
#define outlight 13     //D7                                  
#define light A0 
int vong=0;                                           
char auth[] = "4da8ea997baf414eb11aadeb41e4fd9f";     
char ssid[] = "khoi-binh";   //                        
char pass[] = "123456789"; //               
                                                      
#define DHTPIN 14       //D5                              
#define DHTTYPE DHT11                                 
DHT dht(DHTPIN, DHTTYPE);                             
BlynkTimer timer;                                   
DS1307 rtc;                                           
int x=0,y=0;
int z,k;
int bien;
WidgetLED led1(V2);
WidgetLED led2(V3);
BLYNK_WRITE(V0)                                       
{
 z = param.asInt();                                  
}

BLYNK_WRITE(V1)  
{                                    
k = param.asInt();                                    
                                                      
}
void setup()                                                                                 
{
servo.attach(12);  //D6
servo.write(10); 
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);                                                               
lcd.init(); 
lcd.init();
lcd.backlight();   
//rtc.set(0,39, 9, 13, 8, 2020); //08:00:00 24.12.2014 //sec, min, hour, day, month, year                                                                          
rtc.start();                                                                                 
dht.begin();                                                                                                                                                      
pinMode(outlight,OUTPUT);
pinMode(quat,OUTPUT);
digitalWrite(outlight,0);
digitalWrite(quat,1);                                                                                                                                                
timer.setInterval(1000L, sendSensor);                                                        
lcd.setCursor(0, 0);
lcd.print("Nguyen Dang Khoi");
lcd.setCursor(0, 1);
lcd.print("& Nguyen An Binh");
delay(3500);
lcd.setCursor(0, 0);
lcd.print("*-*  DHSPKT  *-*");
lcd.setCursor(0, 1);
lcd.print("Class: 18641SP2 ");
 delay(3500);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("  :   H:    T:   ");
lcd.setCursor(0,1);
lcd.print("  /  /      L:   ");
}

void hienthi(){
uint8_t sec, min, hour, day, month;
uint16_t year;
  rtc.get(&sec, &min, &hour, &day, &month, &year);    
  lcd.setCursor(0,0);                                 
  lcd.print(hour/10, DEC);  
  lcd.setCursor(1,0);
  lcd.print(hour%10, DEC);
  
  lcd.setCursor(3,0);
  lcd.print(min/10, DEC);
  lcd.setCursor(4,0);
  lcd.print(min%10, DEC);
  
  lcd.setCursor(0,1);
  lcd.print(day/10, DEC);
  lcd.setCursor(1,1);
  lcd.print(day%10, DEC);
  
  lcd.setCursor(3,1);
  lcd.print(month/10, DEC);
  lcd.setCursor(4,1);
  lcd.print(month%10, DEC);
    
  lcd.setCursor(6,1);
  lcd.print(year, DEC);
  
  Serial.print("\nTime: ");
  Serial.print(hour, DEC);
  Serial.print(":");
  Serial.print(min, DEC);
  Serial.print(":");
  Serial.print(sec, DEC);

  Serial.print("\nDate: ");
  Serial.print(day, DEC);
  Serial.print(".");
  Serial.print(month, DEC);
  Serial.print(".");
  Serial.print(year, DEC);
  }
void sendSensor()
{ int value= map(analogRead(light),0,1023,100,0);                                               
  int h = dht.readHumidity();                 
  int t = dht.readTemperature();              
  lcd.setCursor(8,0);                         
  lcd.print(h,1);                               
  lcd.setCursor(14,0);
  lcd.print(t,1);
  lcd.setCursor(14,1);
  lcd.print(value/10);
  lcd.setCursor(15,1);
  lcd.print(value%10);

 if (value<60){servo.write(10);  }    
 if (value>70){servo.write(110); Blynk.notify("Dong rem cua");}    
 if (t>35 ){digitalWrite(quat,0);Blynk.notify("Canh bao! nhiet do tren 35.C");}
 if (z==1){digitalWrite(quat,0);led1.on();}
 if (t<35 && z==0){digitalWrite(quat,1); led1.off();}   
 if (k==1){digitalWrite(outlight,1);led2.on();  }  
 if (k==0){digitalWrite(outlight,0); led2.off();  }   
                                                
  Blynk.virtualWrite(V5, h);                                                                 
  Blynk.virtualWrite(V6, t);                                                                 
  Blynk.virtualWrite(V7, value); 
}

void loop()
{
 hienthi();
 sendSensor();
 Blynk.run();
 timer.run();
}
