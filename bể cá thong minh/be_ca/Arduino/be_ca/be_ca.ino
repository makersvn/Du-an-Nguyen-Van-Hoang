#include <DHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
SoftwareSerial Serial2(2,3);
#include <Servo.h>
Servo servo; 
#define phao 5 // D5
#define coi 6 // D6
#define DHTPIN 4  // D4  
#define PHSensor A0
#define doduc A1 
#define motorin A2 // on: high 
#define motorout A3 // on: low 
#define pump 7 // 

LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int bom, chedo;
int PH;
int h, t, value;
unsigned long int avgValue;
float b;
int buf[10], temp;
String A,B,C,D;

byte abc[]={
  B00111,
  B00101,
  B00111,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000};



void Sensor() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  value= map(analogRead(doduc),0,1023,0,100);

 if ( value>98){ 
  value= 98; 
  }
  
 if (digitalRead(pump) == 1 && value> 85) {
    digitalWrite(motorin, 1);
    lcd.setCursor(13, 0);
    lcd.print("OFF");
  }
 else if (digitalRead(pump) == 0 || value <85) {
    digitalWrite(motorin, 0);
    lcd.setCursor(13, 0);
    lcd.print("ON ");
  }

  for (int i = 0; i < 10; i++) //lấy mẫu của 10 lần
  {
    buf[i] = analogRead(PHSensor);
    delay(10);
  }
  for (int i = 0; i < 9; i++) //sắp xếp giá trị từ nhỏ đến lớn
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  avgValue = 0;
  for (int i = 2; i < 8; i++)               //Lấy số trung bình của 6 lần đo
    avgValue += buf[i];
  float phValue = (float)avgValue * 5.0 / 1024 / 6;   //Chuyển từ Analog sang milivol
  PH = 3.5 * phValue;                  //Chuyển Milivol sang độ PH

  
  A=String(value);
  B=String(t);  
  C=String(h); 
  D=String(PH);
  A+=B;
  A+=C;
  A+=D;
  lcd.setCursor(4, 1);
  lcd.print(value);
  lcd.setCursor(12, 1);
  lcd.print(t);
  lcd.setCursor(3, 0);
  lcd.print(PH);
 delay(100);

}
void mucnuoc() {
  if (digitalRead(phao) == 1 ) {
    digitalWrite(coi, 0);
    digitalWrite(motorout, 0);

  }
 else {
    digitalWrite(coi, 1);
    digitalWrite(motorout, 1);

  }

 

}


void setup()
{
  Serial.begin(9600);
  Serial2.begin(9600);
  servo.attach(12); 
  servo.write(90);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0,abc);
  pinMode(coi, OUTPUT);
  pinMode(motorin, OUTPUT);
  pinMode(motorout, OUTPUT);
  pinMode(phao, INPUT_PULLUP);
  pinMode(pump, INPUT);
  pinMode(doduc, INPUT_PULLUP);
  digitalWrite(coi, 0);
  digitalWrite(motorin, 1);
  dht.begin();
  lcd.setCursor(0, 0);
  lcd.print("     De tai:    ");
  lcd.setCursor(0, 1);
  lcd.print("Be Ca Thong Minh");
  delay(5000);
  lcd.setCursor(0, 0);
  lcd.print("Nguyen Hoai Nam ");
  lcd.setCursor(0, 1);
  lcd.print("Mssv: 2202180036");
  delay(5000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("PH:      Bom:OFF");
  lcd.setCursor(0, 1);
  lcd.print("NTU:   %  T:   C");
  lcd.setCursor(14, 1);
  lcd.write(abc);
}
void loop()
{

Sensor(); 
mucnuoc();
Serial2.println(A);
Serial.println(A);
delay(800);

}
