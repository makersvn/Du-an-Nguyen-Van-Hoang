
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DS1307.h>
#include <EEPROM.h>
Servo servo;
Servo servo1;
Servo servo2;
Servo servo3;
uint8_t sec, min, hour, day, month;
uint16_t year;
DS1307 rtc;
LiquidCrystal_I2C lcd(0x27,20,4);
#define SS_PIN 8
#define RST_PIN 7
#define sensor A0
#define sensor1 A1
#define sensor2 A2
#define sensor3 A3

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key key; 

char j;
int val=0,val1=0,val2=0,val3=0;
int dem=0,vong=0;
int error=0;
byte nuidPICC[]={0xE9, 0xBF, 0x7A, 0x3C},
nuidPICC1[]={0x99, 0x94, 0x7E, 0x3C}, 
nuidPICC2[]={0x49, 0x08, 0x7D, 0x3C},
nuidPICC3[]={0x19, 0x43, 0xC5, 0x3C};

byte cus[] = {
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100,
  B00100
};
int i,tang=0, bien;


void hienthi(){
  rtc.get(&sec, &min, &hour, &day, &month, &year);
  lcd.setCursor(0,2);
  lcd.print(" Vi tri | Trang thai");
  lcd.setCursor(0,3);
  lcd.print("        |           ");
  lcd.setCursor(10,0);
  lcd.print(hour/10, DEC);
  lcd.setCursor(11,0);
  lcd.print(hour%10, DEC);
  
  lcd.setCursor(13,0);
  lcd.print(min/10, DEC);
  lcd.setCursor(14,0);
  lcd.print(min%10, DEC);
  
  lcd.setCursor(8,1);
  lcd.print(day/10, DEC);
  lcd.setCursor(9,1);
  lcd.print(day%10, DEC);
  
  lcd.setCursor(11,1);
  lcd.print(month/10, DEC);
  lcd.setCursor(12,1);
  lcd.print(month%10, DEC);
    
  lcd.setCursor(14,1);
  lcd.print(year, DEC);

  }
void setup() { 
Serial.begin(9600);
servo.attach(3); 
servo1.attach(5); 
servo2.attach(6); 
servo3.attach(9);
servo.write(100);
servo1.write(98);
servo2.write(98);
servo3.write(98);
SPI.begin(); 
rtc.start();
//rtc.set(0, 31, 21, 23, 10, 2019); //08:00:00 24.12.2014 //sec, min, hour, day, month, year
lcd.init(); 
lcd.backlight(); 
lcd.createChar(1, cus); 
rfid.PCD_Init();
lcd.setCursor(0, 0);
lcd.print("--------------------");
lcd.setCursor(0, 1);
lcd.print("    Le Vinh Thinh   ");
lcd.setCursor(0, 2);
lcd.print("  MSSV: 2202180032  ");
lcd.setCursor(0, 3);
lcd.print("--------------------");
delay(3300);
lcd.setCursor(0, 1);
lcd.print("    Do an mon hoc   ");
lcd.setCursor(0, 2);
lcd.print(" Nha xe thong minh  ");
delay(3300);
lcd.setCursor(0,0);
lcd.print("Time :      :       ");
lcd.setCursor(0,1);
lcd.print("Date :    /  /      ");
lcd.setCursor(0,2);
lcd.print(" Vi tri | Trang thai");
lcd.setCursor(0,3);
lcd.print("        |           ");
}


void door(){

  if ( ! rfid.PICC_IsNewCardPresent())
    return;

  // Verify if the NUID has been readed
  if ( ! rfid.PICC_ReadCardSerial())
    return;

if (
rfid.uid.uidByte[0] == nuidPICC[0] &&
rfid.uid.uidByte[1] == nuidPICC[1] &&
rfid.uid.uidByte[2] == nuidPICC[2] &&  
rfid.uid.uidByte[3] == nuidPICC[3] ) {
val++;
lcd.setCursor(1,3);
lcd.print("Cot A");

if(val==1){
lcd.setCursor(12,3);
lcd.print("Gui xe");
while(digitalRead(sensor)==1){servo.write(10);};
servo.write(100);
delay(100);
}

if(val==2){
lcd.setCursor(12,3);
lcd.print("Lay xe");
servo.write(10);
delay(200);
while(digitalRead(sensor)==0);
delay(1000);
servo.write(100);
delay(100);
val=0;
}}
////-------------------------------------------------------------------------------

if (
rfid.uid.uidByte[0] == nuidPICC1[0] &&
rfid.uid.uidByte[1] == nuidPICC1[1] &&
rfid.uid.uidByte[2] == nuidPICC1[2] &&  
rfid.uid.uidByte[3] == nuidPICC1[3] ) {
val1++;
lcd.setCursor(1,3);
lcd.print("  Cot B  ");

if(val1==1){
lcd.setCursor(12,3);
lcd.print("Gui xe");
while(digitalRead(sensor1)==1){servo1.write(5);};
servo1.write(98);
delay(100);
}

if(val1==2){
lcd.setCursor(12,3);
lcd.print("Lay xe");
servo1.write(5);
delay(200);
while(digitalRead(sensor1)==0);
delay(1000);
servo1.write(98);
delay(100);
val1=0;
}}

// //---------------------------------------------------------------------------------
if (
rfid.uid.uidByte[0] == nuidPICC2[0] &&
rfid.uid.uidByte[1] == nuidPICC2[1] &&
rfid.uid.uidByte[2] == nuidPICC2[2] &&  
rfid.uid.uidByte[3] == nuidPICC2[3] ) {
val2++;
lcd.setCursor(1,3);
lcd.print("Cot C");

if(val2==1){
lcd.setCursor(12,3);
lcd.print("Gui xe");
while(digitalRead(sensor2)==1){servo2.write(5);};
servo2.write(98);
delay(100);
}

if(val2==2){
lcd.setCursor(12,3);
lcd.print("Lay xe");
servo2.write(5);
delay(200);
while(digitalRead(sensor2)==0);
delay(1000);
servo2.write(98);
delay(100);
val2=0;
}}

//-----------------------------------------------------------------------------------
 if (
rfid.uid.uidByte[0] == nuidPICC3[0] &&
rfid.uid.uidByte[1] == nuidPICC3[1] &&
rfid.uid.uidByte[2] == nuidPICC3[2] &&  
rfid.uid.uidByte[3] == nuidPICC3[3] ) {
val3++;
lcd.setCursor(1,3);
lcd.print("Cot D");

if(val3==1){
lcd.setCursor(12,3);
lcd.print("Gui xe");
while(digitalRead(sensor3)==1){servo3.write(5);};
servo3.write(98);
delay(100);
}

if(val3==2){
lcd.setCursor(12,3);
lcd.print("Lay xe");
servo3.write(5);
delay(200);
while(digitalRead(sensor3)==0);
delay(1000);
servo3.write(98);
delay(100);
val3=0;
}}


 //------------------------------------------------------------------------------------
 if (
rfid.uid.uidByte[0] != nuidPICC[0] &&
rfid.uid.uidByte[0] != nuidPICC1[0] &&
rfid.uid.uidByte[0] != nuidPICC2[0] &&  
rfid.uid.uidByte[0] != nuidPICC3[0] ){   

lcd.setCursor(0,2);
lcd.print("    Ma the sai!!!   ");
lcd.setCursor(0,3);
lcd.print(" Vui long doi:    % ");
for(error=0;error<=100;error++){
lcd.setCursor(15,3);
lcd.print(error);
delay(500);  }
lcd.setCursor(0,3);
lcd.print("  Scan card again   "); 
delay(3000);



}

  rfid.PCD_StopCrypto1();
  
}
    

void loop() {
door();
hienthi();

}
