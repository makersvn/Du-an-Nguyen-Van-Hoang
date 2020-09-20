#include <Wire.h> 
#include<LiquidCrystal_I2C.h>;
#define motoLeft1 11
#define motoLeft2 10
#define motoRight1 6
#define motoRight2 5
LiquidCrystal_I2C lcd(0x27,16,2);
int val;

void setup() {
  Serial.begin(9600);
  pinMode(motoLeft1, OUTPUT);
  pinMode(motoLeft2, OUTPUT);
  pinMode(motoRight1, OUTPUT);
  pinMode(motoRight2, OUTPUT);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print(" Tran Van Quyet ");
  lcd.setCursor(0,1);
  lcd.print("Lop: 08DHLDT_CT "); 
  delay(2500) ;
  lcd.setCursor(0,0);
  lcd.print("*-* PROJECT *-*");  
  lcd.setCursor(0,1);
  lcd.print(" BLUETOOTH CAR "); 
  delay(2000);
  lcd.setCursor(0,0);
  lcd.print("*-*  Status  *-*");  
  lcd.setCursor(0,1);
  lcd.print("      Stop      "); 
}

void hc05(){
  if (Serial.available()>0){
    val=Serial.read(); 
    switch(val)
   {
  case 'S' :
      lcd.setCursor(0,1);
      lcd.print("      Stop      "); 
      ngung();
      break;
   case 'F' :
      lcd.setCursor(0,1);
      lcd.print("    Forward    "); 
      forward();
      break;
   case 'B' :
      lcd.setCursor(0,1);
      lcd.print("    Backward   "); 
      backward();
     break;
   case 'L' :
     lcd.setCursor(0,1);
     lcd.print("      Left      "); 
     turnLeft();
     break;
   case 'R' :
    lcd.setCursor(0,1);
    lcd.print("      Right     ");                           
    turnRight();
    break;
  }
  
  }}
void dongcotrai(int x, int y){
analogWrite(motoLeft1,x);
analogWrite(motoLeft2,y);
}
void dongcophai(int j,int k){
analogWrite(motoRight1,j);
analogWrite(motoRight2,k);
}
void forward(){
dongcotrai(0,255);
dongcophai(0,255);
}
void backward(){
dongcotrai(255,0);
dongcophai(255,0);
}
void ngung(){
dongcotrai(0,0);
dongcophai(0,0);
}
void turnLeft(){
dongcotrai(255,0);
dongcophai(0,255);
}
void turnRight(){
dongcotrai(0,255);
dongcophai(255,0);
}


void loop() {
hc05();
}
